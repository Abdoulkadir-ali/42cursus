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
	void		*uncomp_data, *final_data;
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
	
	printf("DEBUG: FBX Array type='%c' alen=%u enc=%u sz=%zu\n", type, arr_len, encoding, actual_sz);
	if (arr_len >= 3)
	{
		if (actual_sz == 8)
			printf("       [0..2]: %f, %f, %f\n", ((double*)uncomp_data)[0], ((double*)uncomp_data)[1], ((double*)uncomp_data)[2]);
		else if (actual_sz == 4 && type == 'f')
			printf("       [0..2]: %f, %f, %f\n", ((float*)uncomp_data)[0], ((float*)uncomp_data)[1], ((float*)uncomp_data)[2]);
		else if (actual_sz == 4)
			printf("       [0..2]: %d, %d, %d\n", ((int*)uncomp_data)[0], ((int*)uncomp_data)[1], ((int*)uncomp_data)[2]);
	}

	printf("       read_fbx_array returning ptr %p\n", (actual_sz == elem_sz) ? uncomp_data : final_data); fflush(stdout);
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
	if (node->name_len > 0 && node->name_len < sizeof(node->name))
		safe_read(fd, node->name, node->name_len);
	printf("   DEBUG: Node name='%s' end=%lu nprops=%lu\n", node->name, (unsigned long)node->end_offset, (unsigned long)node->num_properties); fflush(stdout);
}

static void	parse_nodes(int fd, uint64_t end_offset, bool is_64, t_fbx_data *d)
{
	t_fbx_bin_node	*n;

	n = malloc(sizeof(t_fbx_bin_node));
	if (!n) return ;
	while ((uint64_t)lseek(fd, 0, SEEK_CUR) < end_offset)
	{
		read_node_header(fd, n, is_64);
		if (n->end_offset == 0)
			break ;
		if (ft_strcmp(n->name, "Vertices") == 0)
		{
			if (!d->v)
				d->v = read_fbx_array(fd, &d->vc, 8);
			else
				skip_properties(fd, n->num_properties);
		}
		else if (ft_strcmp(n->name, "PolygonVertexIndex") == 0 && d->v)
		{
			if (!d->ri)
				d->ri = (int*)read_fbx_array(fd, &d->rc, 4);
			else
				skip_properties(fd, n->num_properties);
		}
		else if (ft_strcmp(n->name, "Normals") == 0 && d->v && !d->vn)
		{
			d->vn = read_fbx_array(fd, &d->nc, 8);
		}
		else if (ft_strcmp(n->name, "UV") == 0 && d->v && !d->vu)
		{
			d->vu = read_fbx_array(fd, &d->uc, 8);
		}
		else
		{
			skip_properties(fd, n->num_properties);
			if ((uint64_t)lseek(fd, 0, SEEK_CUR) < n->end_offset)
				parse_nodes(fd, n->end_offset, is_64, d);
		}
		lseek(fd, (off_t)n->end_offset, SEEK_SET);
	}
	free(n);
}

bool	parse_fbx_binary(const char *path, t_scene *scene)
{
	int				fd;
	char			header[23];
	uint32_t		version;
	t_skinned_mesh	mesh;
	t_fbx_data		d;

	printf("DEBUG: parse_fbx_binary starting for %s\n", path); fflush(stdout);
	if ((fd = open(path, O_RDONLY)) < 0)
		return (false);
	if (read(fd, header, 23) < 23 || read(fd, &version, 4) < 4)
	{
		printf("DEBUG ERR: Failed to read FBX binary header\n"); fflush(stdout);
		return (close(fd), false);
	}
	printf("DEBUG: FBX Binary Version: %u\n", version); fflush(stdout);
	ft_memset(&mesh, 0, sizeof(t_skinned_mesh));
	ft_memset(&d, 0, sizeof(t_fbx_data));
	mesh.base.name = ft_strdup(path);
	printf("DEBUG: starting parse_nodes recursion\n"); fflush(stdout);
	parse_nodes(fd, (uint64_t)-1, version >= 7500, &d);
	close(fd);
	printf("DEBUG: parse_nodes recursion finished\n"); fflush(stdout);
	if (!d.v || !d.ri)
	{
		free(mesh.base.name);
		free(d.v); free(d.ri); free(d.vn); free(d.vu);
		return (false);
	}
	if (d.vc > 1000000)
	{
		printf("ERROR: FBX mesh too large (%d vertices, limit 1M)\n", d.vc);
		free(mesh.base.name);
		free(d.v); free(d.ri); free(d.vn); free(d.vu);
		return (false);
	}
	mesh.base.vertices = d.v;
	fbx_build_flat(&mesh.base, d.ri, d.rc, d.vn, d.nc, d.vu, d.uc, d.vc);
	if (d.vn) free(d.vn);
	if (d.vu) free(d.vu);
	free(d.ri);
	if (mesh.base.tri_count == 0)
	{
		free(mesh.base.name);
		free(mesh.base.vertices);
		return (false);
	}
	mesh.vertex_count = mesh.base.tri_count * 3;
	mesh.base.vertex_count = mesh.base.tri_count * 3;
	mesh_build_bvh(&mesh.base);
	printf("FBX Binary Loaded: %s (%d tris)\n", path, mesh.base.tri_count);
	return (scene_add_animated(scene, mesh));
}
