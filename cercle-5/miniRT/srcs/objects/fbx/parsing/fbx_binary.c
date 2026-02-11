/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:20:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include <fcntl.h>
#include <zlib.h>
#include <float.h>

typedef struct s_fbx_data
{
	t_vec3		*v;
	uint32_t	vc;
	int			*ri;
	uint32_t	rc;
	t_vec3		*vn;
	uint32_t	nc;
	t_vec2		*vu;
	uint32_t	uc;
}	t_fbx_data;

static ssize_t	safe_read(int fd, void *buf, size_t count)
{
	return (read(fd, buf, count));
}

static void	*read_fbx_array(int fd, uint32_t *count, size_t elem_sz)
{
	uint32_t	arr_len, encoding, comp_len;
	void		*uncomp_data = NULL, *final_data = NULL;
	uLongf		uncomp_len;
	char		type;
	size_t      actual_sz;

	if (safe_read(fd, &type, 1) < 1) return (NULL);
	if (type == 'd') actual_sz = 8;
	else if (type == 'f' || type == 'i') actual_sz = 4;
	else if (type == 'l' || type == 'b' || type == 'c') actual_sz = (type == 'l' ? 8 : 1);
	else return (NULL);
	if (safe_read(fd, &arr_len, 4) < 4 || safe_read(fd, &encoding, 4) < 4 \
		|| safe_read(fd, &comp_len, 4) < 4)
		return (NULL);
	if (arr_len > 20000000) return (NULL);
	uncomp_len = arr_len * actual_sz;
	uncomp_data = malloc(uncomp_len > 0 ? uncomp_len : 1);
	if (!uncomp_data) return (NULL);
	if (encoding == 0)
	{
		if (safe_read(fd, uncomp_data, uncomp_len) < (ssize_t)uncomp_len)
			return (free(uncomp_data), NULL);
	}
	else
	{
		void *comp_data = malloc(comp_len > 0 ? comp_len : 1);
		if (!comp_data) return (free(uncomp_data), NULL);
		if (safe_read(fd, comp_data, comp_len) < (ssize_t)comp_len)
			return (free(comp_data), free(uncomp_data), NULL);
		if (uncompress(uncomp_data, &uncomp_len, comp_data, comp_len) != Z_OK)
			return (free(comp_data), free(uncomp_data), NULL);
		free(comp_data);
	}
	
	if (actual_sz == elem_sz) {
		*count = arr_len;
		return (uncomp_data);
	}
	final_data = malloc(arr_len * elem_sz);
	if (!final_data) return (free(uncomp_data), NULL);
	if (actual_sz == 4 && elem_sz == 8)
	{
		float *src = uncomp_data;
		double *dst = final_data;
		uint32_t i = -1;
		while (++i < arr_len) dst[i] = (double)src[i];
	}
	else ft_memcpy(final_data, uncomp_data, arr_len * (actual_sz < elem_sz ? actual_sz : elem_sz));
	free(uncomp_data);
	*count = arr_len;
	return (final_data);
}

static void	skip_properties(int fd, uint64_t num_props)
{
	uint64_t	i;
	char		type;
	uint32_t	alen, enc, clen, slen;
	size_t      isz;

	i = 0;
	while (i < num_props)
	{
		if (safe_read(fd, &type, 1) < 1) break;
		if (type == 'Y') lseek(fd, 2, SEEK_CUR);
		else if (type == 'C') lseek(fd, 1, SEEK_CUR);
		else if (type == 'I' || type == 'F') lseek(fd, 4, SEEK_CUR);
		else if (type == 'D' || type == 'L') lseek(fd, 8, SEEK_CUR);
		else if (type == 'S' || type == 'R')
		{
			safe_read(fd, &slen, 4);
			lseek(fd, slen, SEEK_CUR);
		}
		else if (ft_strchr("dflicb", type))
		{
			if (safe_read(fd, &alen, 4) < 4 || safe_read(fd, &enc, 4) < 4 \
				|| safe_read(fd, &clen, 4) < 4) break;
			if (enc == 1) lseek(fd, clen, SEEK_CUR);
			else
			{
				isz = (type == 'd' || type == 'l') ? 8 : ((type == 'f' || type == 'i') ? 4 : 1);
				lseek(fd, (uint64_t)alen * isz, SEEK_CUR);
			}
		}
		i++;
	}
}

static void	read_offsets(int fd, t_fbx_bin_node *node, bool is_64bit)
{
	uint32_t	tmp;

	if (is_64bit)
	{
		safe_read(fd, &node->end_offset, 8);
		safe_read(fd, &node->num_properties, 8);
		safe_read(fd, &node->property_list_len, 8);
	}
	else
	{
		safe_read(fd, &tmp, 4);
		node->end_offset = tmp;
		safe_read(fd, &tmp, 4);
		node->num_properties = tmp;
		safe_read(fd, &tmp, 4);
		node->property_list_len = tmp;
	}
}

static void	read_node_header(int fd, t_fbx_bin_node *node, bool is_64bit)
{
	read_offsets(fd, node, is_64bit);
	if (safe_read(fd, &node->name_len, 1) < 1)
	{
		node->end_offset = 0;
		return ;
	}
	ft_memset(node->name, 0, sizeof(node->name));
	if (node->name_len > 0)
	{
		size_t name_limit = sizeof(node->name) - 1;
		size_t to_read = node->name_len;
		if (to_read > name_limit)
			to_read = name_limit;
		safe_read(fd, node->name, to_read);
		if (node->name_len > to_read) lseek(fd, node->name_len - to_read, SEEK_CUR);
	}
}

static void	parse_nodes(int fd, uint64_t end_offset, bool is_64, t_fbx_data *d, int depth)
{
	t_fbx_bin_node	n;

	if (depth > 20) return ;
	while ((uint64_t)lseek(fd, 0, SEEK_CUR) < end_offset)
	{
		read_node_header(fd, &n, is_64);
		if (n.end_offset == 0)
			break ;
		if (ft_strcmp(n.name, "Vertices") == 0 && !d->v)
		{
			ft_print_debug("   Depth %d: Reading Vertices...\n", depth);
			d->v = read_fbx_array(fd, &d->vc, 8);
			if (d->v)
			{
				ft_print_debug("   Depth %d: Got Vertices: %u floats\n", depth, d->vc);
				d->vc /= 3;
			}
		}
		else if (ft_strcmp(n.name, "PolygonVertexIndex") == 0 && !d->ri)
		{
			ft_print_debug("   Depth %d: Reading Indices...\n", depth);
			d->ri = (int*)read_fbx_array(fd, &d->rc, 4);
			ft_print_debug("   Depth %d: Got Indices: %u\n", depth, d->rc);
		}
		else if (ft_strcmp(n.name, "Normals") == 0 && !d->vn)
		{
			ft_print_debug("   Depth %d: Reading Normals...\n", depth);
			d->vn = read_fbx_array(fd, &d->nc, 8);
			if (d->vn)
			{
				ft_print_debug("   Depth %d: Got Normals: %u floats\n", depth, d->nc);
				d->nc /= 3;
			}
		}
		else if (ft_strcmp(n.name, "UV") == 0 && !d->vu)
		{
			ft_print_debug("   Depth %d: Reading UVs...\n", depth);
			d->vu = read_fbx_array(fd, &d->uc, 8);
			if (d->vu)
			{
				ft_print_debug("   Depth %d: Got UVs: %u floats\n", depth, d->uc);
				d->uc /= 2;
			}
		}
		else
		{
			skip_properties(fd, n.num_properties);
			if ((uint64_t)lseek(fd, 0, SEEK_CUR) < n.end_offset)
				parse_nodes(fd, n.end_offset, is_64, d, depth + 1);
		}
		if (lseek(fd, (off_t)n.end_offset, SEEK_SET) == (off_t)-1) break ;
	}
}

static t_vec3	*repack_doubles_to_vec3(double *raw, uint32_t count)
{
	t_vec3		*out;
	uint32_t	i;

	out = ft_calloc(count, sizeof(t_vec3));
	if (!out)
		return (NULL);
	i = 0;
	while (i < count)
	{
		out[i].x = raw[i * 3];
		out[i].y = raw[i * 3 + 1];
		out[i].z = raw[i * 3 + 2];
		out[i].w = 0.0;
		i++;
	}
	return (out);
}

bool	parse_fbx_binary(const char *path, t_scene *scene)
{
	int				fd;
	char			header[64];
	uint32_t		version;
	t_skinned_mesh	mesh;
	t_fbx_data		d;

	ft_print_debug("DEBUG: parse_fbx_binary starting for %s\n", path);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (false);
	if (read(fd, header, 23) < 23 || read(fd, &version, 4) < 4)
	{
		fprintf(stderr, "Error: Failed to read FBX binary header\n");
		return (close(fd), false);
	}
	ft_print_debug("DEBUG: FBX Binary Version: %u\n", version);
	ft_memset(&mesh, 0, sizeof(t_skinned_mesh));
	ft_memset(&d, 0, sizeof(t_fbx_data));
	mesh.base.name = ft_strdup(path);
	ft_print_debug("DEBUG: starting parse_nodes recursion\n");
	parse_nodes(fd, (uint64_t)-1, version >= 7500, &d, 0);
	close(fd);
	ft_print_debug("DEBUG: parse_nodes finished. counts: vc=%u nc=%u\n", d.vc, d.nc);
	if (!d.v || !d.ri)
	{
		fprintf(stderr, "Error: FBX missing critical data\n");
		free(mesh.base.name);
		free(d.v); free(d.ri); free(d.vn); free(d.vu);
		return (false);
	}
	if (d.vc > 1000000)
	{
		fprintf(stderr, "Error: FBX mesh too large (%d vertices, limit 1M)\n", d.vc);
		free(mesh.base.name);
		free(d.v); free(d.ri); free(d.vn); free(d.vu);
		return (false);
	}
	mesh.base.vertices = repack_doubles_to_vec3((double *)d.v, d.vc);
	free(d.v);
	d.v = NULL;
	if (d.vn)
	{
		t_vec3 *rn = repack_doubles_to_vec3((double *)d.vn, d.nc);
		free(d.vn);
		d.vn = rn;
	}
	ft_print_debug("DEBUG: calling fbx_build_flat\n");
	fbx_build_flat(&mesh.base, d.ri, (int)d.rc, d.vn, (int)d.nc, d.vu, (int)d.uc, (int)d.vc);
	ft_print_debug("DEBUG: fbx_build_flat finished\n");
	if (d.vn) free(d.vn);
	if (d.vu) free(d.vu);
	free(d.ri);
	if (mesh.base.tri_count == 0)
	{
		mesh_free(&mesh.base);
		return (false);
	}
	mesh_build_bvh(&mesh.base);
	ft_print_debug("FBX Binary Loaded: %s (%d tris)\n", path, mesh.base.tri_count);
	return (scene_add_animated(scene, mesh));
}
