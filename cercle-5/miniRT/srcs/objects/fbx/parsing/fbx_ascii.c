/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static char	*resolve_fbx_path(const char *fbx_path, const char *tex_filename)
{
	char	*dir;
	char	*full_path;

	dir = path_get_dir(fbx_path);
	if (!dir)
		return (ft_strdup(tex_filename));
	full_path = ft_strjoin(dir, tex_filename);
	free(dir);
	return (full_path);
}

static char	*fbx_next(char *p)
{
	while (*p && !ft_isdigit(*p) && *p != '-' && *p != '.' && *p != '}')
	{
		if (*p == 'a' && *(p + 1) == ':')
			p += 2;
		else
			p++;
	}
	return (p);
}

static char	*find_node(char *p, char *end, const char *name)
{
	size_t	name_len;

	if (!p || !name)
		return (NULL);
	name_len = ft_strlen(name);
	while (p + name_len <= end)
	{
		if (ft_memcmp(p, (void *)name, name_len) == 0)
			return (p + name_len);
		p++;
	}
	return (NULL);
}

static int	parse_texture(char *p, char *end, t_scene *scene, const char *fbx_path)
{
	char	*fn_start;
	char	*fn_end;
	char	*filename;
	char	*full_path;
	int		mat_id;

	if (!(p = find_node(p, end, "Texture:")) || !(p = find_node(p, end, "FileName:")))
		return (-1);
	while (p < end && *p && *p != '"') p++;
	if (p >= end || *p != '"') return (-1);
	p++;
	fn_start = p;
	while (p < end && *p && *p != '"') p++;
	if (p >= end || *p != '"') return (-1);
	fn_end = p;
	
	filename = ft_substr(fn_start, 0, fn_end - fn_start);
	full_path = resolve_fbx_path(fbx_path, filename);
	free(filename);
	
	mat_id = scene_add_named_material(scene, "FBX_Mat");
	if (load_texture_xpm(scene, &scene->materials[mat_id].albedo_map, full_path))
		ft_print_debug("FBX Texture Loaded: %s\n", full_path);
	free(full_path);
	return (mat_id);
}

static void	*parse_array(char **p, int *count, size_t sz, void (*f)(char **, void *))
{
	size_t	cap;
	size_t	i;
	void	*arr;

	cap = 10000;
	i = 0;
	arr = malloc(sz * cap);
	if (!arr)
		return (NULL);
	while (**p && **p != '}')
	{
		*p = fbx_next(*p);
		if (!**p || **p == '}')
			break ;
		if (!dynarray_ensure(&arr, i, &cap, sz))
			return (free(arr), NULL);
		f(p, (char *)arr + (i * sz));
		i++;
	}
	*count = (int)i;
	return (arr);
}

static void	f_vec3(char **p, void *dst)
{
	t_vec3	*v;

	v = (t_vec3 *)dst;
	v->x = strtod(*p, p);
	*p = fbx_next(*p);
	v->y = strtod(*p, p);
	*p = fbx_next(*p);
	v->z = strtod(*p, p);
	if (**p == ',') (*p)++;
}

static void	f_vec2(char **p, void *dst)
{
	t_vec2	*v;

	v = (t_vec2 *)dst;
	v->x = strtod(*p, p);
	*p = fbx_next(*p);
	v->y = strtod(*p, p);
	if (**p == ',') (*p)++;
}

static void	f_int(char **p, void *dst)
{
	*(int *)dst = ft_atoi(*p);
	if (**p == '-')
		(*p)++;
	while (ft_isdigit(**p))
		(*p)++;
	if (**p == ',') (*p)++;
}

static char	*read_file_content(const char *path, size_t *out_size)
{
	int			fd;
	struct stat	st;
	char		*buf;
	ssize_t		ret;
	size_t		total_read;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (fstat(fd, &st) < 0 || st.st_size == 0)
	{
		close(fd);
		return (NULL);
	}
	buf = malloc(st.st_size + 1);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	total_read = 0;
	while (total_read < (size_t)st.st_size)
	{
		ret = read(fd, buf + total_read, st.st_size - total_read);
		if (ret <= 0)
			break ;
		total_read += ret;
	}
	buf[total_read] = '\0';
	close(fd);
	*out_size = total_read;
	return (buf);
}

static char	*advance_to_data(char *p, char *end)
{
	size_t rem = end - p;
	if (rem > 500) rem = 500;
	
	char *data_start = ft_strnstr(p, "a:", rem);
	if (data_start)
		return (data_start + 2);
	return (p);
}

bool	parse_fbx_ascii(const char *path, t_scene *scene)
{
	t_skinned_mesh	m;
	t_vec3			*rn;
	t_vec2			*ru;
	int				*ri;
	char			*buf;
	char			*p;
	char			*end;
	char			*temp;
	size_t			buf_size;
	int				rc, vc, nc, uc;
	int				mat_id;

	rc = vc = nc = uc = 0;
	buf = read_file_content(path, &buf_size);
	if (!buf)
		return (false);
	p = buf;
	end = buf + buf_size;
	ft_memset(&m, 0, sizeof(t_skinned_mesh));
	m.base.name = ft_strdup(path);
	
	if (!(p = find_node(p, end, "Vertices:")))
	{
		free(buf);
		return (false);
	}
	p = advance_to_data(p, end);
	m.base.vertices = parse_array(&p, &vc, sizeof(t_vec3), f_vec3);
	
	if (!(p = find_node(p, end, "PolygonVertexIndex:")))
	{
		mesh_free(&m.base);
		free(buf);
		return (false);
	}
	p = advance_to_data(p, end);
	ri = parse_array(&p, &rc, sizeof(int), f_int);

	rn = NULL;
	if ((temp = find_node(p, end, "Normals:"))) 
	{
		temp = advance_to_data(temp, end);
		rn = parse_array(&temp, &nc, sizeof(t_vec3), f_vec3);
	}

	ru = NULL;
	if ((temp = find_node(p, end, "UV:")))
	{
		temp = advance_to_data(temp, end);
		ru = parse_array(&temp, &uc, sizeof(t_vec2), f_vec2);
	}
	
	if (!m.base.vertices || !ri)
	{
		mesh_free(&m.base);
		if (ri) free(ri);
		if (rn) free(rn);
		if (ru) free(ru);
		free(buf);
		return (false);
	}
	fbx_build_flat(&m.base, ri, rc, rn, nc, ru, uc, vc);
	if (rn) free(rn);
	if (ru) free(ru);
	free(ri);
	m.vertex_count = m.base.tri_count * 3;
	m.base.vertex_count = m.base.tri_count * 3;
	mesh_build_bvh(&m.base);
	mat_id = parse_texture(p, end, scene, path);
	if (mat_id >= 0)
		m.base.mat_id = mat_id;
	
	free(buf);
	return (scene_add_animated(scene, m));
}
