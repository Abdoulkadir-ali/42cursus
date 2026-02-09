/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fbx_ascii.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:15:00 by abdoali           #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static char	*find_node(int fd, const char *name)
{
	char	*line;
	long	pos;

	pos = 0;
	while ((line = get_next_line(fd)))
	{
		pos += ft_strlen(line);
		if (ft_strnstr(line, name, ft_strlen(line)))
			return (line);
		free(line);
		if (pos > 1000000000)
			break ;
	}
	return (NULL);
}

static char	*fbx_next(char *p)
{
	while (*p && !ft_isdigit(*p) && *p != '-' && *p != '.')
	{
		if (*p == 'a' && *(p + 1) == ':')
			p += 2;
		else
			p++;
	}
	return (p);
}

static t_vec3	*parse_vec3(int fd, int *count)
{
	int		cap;
	int		i;
	t_vec3	*arr;
	void	*tmp;
	char	*line;
	char	*p;

	cap = 10000;
	i = 0;
	arr = malloc(sizeof(t_vec3) * cap);
	if (!arr)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (ft_strchr(line, '}'))
		{
			free(line);
			break ;
		}
		p = line;
		while (*p)
		{
			p = fbx_next(p);
			if (!*p)
				break ;
			if (i >= cap)
			{
				cap *= 2;
				tmp = realloc(arr, sizeof(t_vec3) * cap);
				if (!tmp)
				{
					free(arr);
					free(line);
					return (NULL);
				}
				arr = tmp;
			}
			arr[i].x = strtod(p, &p);
			p = fbx_next(p);
			arr[i].y = strtod(p, &p);
			p = fbx_next(p);
			arr[i].z = strtod(p, &p);
			i++;
		}
		free(line);
	}
	*count = i;
	return (arr);
}

static t_vec2	*parse_vec2(int fd, int *count)
{
	int		cap;
	int		i;
	t_vec2	*arr;
	void	*tmp;
	char	*line;
	char	*p;

	cap = 10000;
	i = 0;
	arr = malloc(sizeof(t_vec2) * cap);
	if (!arr)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (ft_strchr(line, '}'))
		{
			free(line);
			break ;
		}
		p = line;
		while (*p)
		{
			p = fbx_next(p);
			if (!*p)
				break ;
			if (i >= cap)
			{
				cap *= 2;
				tmp = realloc(arr, sizeof(t_vec2) * cap);
				if (!tmp)
				{
					free(arr);
					free(line);
					return (NULL);
				}
				arr = tmp;
			}
			arr[i].x = strtod(p, &p);
			p = fbx_next(p);
			arr[i].y = strtod(p, &p);
			i++;
		}
		free(line);
	}
	*count = i;
	return (arr);
}

static int	*parse_indices(int fd, int *count)
{
	int		cap;
	int		i;
	int		*arr;
	void	*tmp;
	char	*line;
	char	*p;

	cap = 10000;
	i = 0;
	arr = malloc(sizeof(int) * cap);
	if (!arr)
		return (NULL);
	while ((line = get_next_line(fd)))
	{
		if (ft_strchr(line, '}'))
		{
			free(line);
			break ;
		}
		p = line;
		while (*p)
		{
			p = fbx_next(p);
			if (!*p)
				break ;
			if (i >= cap)
			{
				cap *= 2;
				tmp = realloc(arr, sizeof(int) * cap);
				if (!tmp)
				{
					free(arr);
					free(line);
					return (NULL);
				}
				arr = tmp;
			}
			arr[i++] = ft_atoi(p);
			if (*p == '-')
				p++;
			while (ft_isdigit(*p))
				p++;
		}
		free(line);
	}
	*count = i;
	return (arr);
}

static void	build_flat(t_mesh *m, int *raw, int raw_c, t_vec3 *n, t_vec2 *u)
{
	t_vec2	*nu;
	t_vec3	*nv;
	t_vec3	*nn;
	int		si;
	int		idx;
	int		vn;
	int		i;
	int		ps;
	int		vp;
	int		vg;
	int		*ni;
	int		v[64];
	int		tc;

	ps = 0;
	vp = 0;
	vg = 0;
	idx = 0;
	vn = 0;
	i = 0;
	tc = 0;
	while (ps < raw_c)
	{
		vn = 0;
		while (ps < raw_c)
		{
			idx = raw[ps++];
			vn++;
			if (idx < 0)
				break ;
		}
		if (vn >= 3)
			tc += (vn - 2);
	}
	m->tri_count = tc;
	nv = malloc(sizeof(t_vec3) * tc * 3);
	nn = n ? malloc(sizeof(t_vec3) * tc * 3) : NULL;
	nu = u ? malloc(sizeof(t_vec2) * tc * 3) : NULL;
	ni = malloc(sizeof(int) * tc * 3);
	if (!nv || !ni || (n && !nn) || (u && !nu))
		return ;
	ps = 0;
	while (ps < raw_c)
	{
		vn = 0;
		si = vg;
		while (ps < raw_c)
		{
			idx = raw[ps++];
			v[vn++] = (idx < 0) ? (idx ^ -1) : idx;
			vg++;
			if (idx < 0 || vn >= 64)
				break ;
		}
		for (i = 1; i < vn - 1; i++)
		{
			nv[vp] = m->vertices[v[0]];
			if (nn)
				nn[vp] = n[si + 0];
			if (nu)
				nu[vp] = u[si + 0];
			ni[vp] = vp;
			vp++;
			nv[vp] = m->vertices[v[i]];
			if (nn)
				nn[vp] = n[si + i];
			if (nu)
				nu[vp] = u[si + i];
			ni[vp] = vp;
			vp++;
			nv[vp] = m->vertices[v[i + 1]];
			if (nn)
				nn[vp] = n[si + i + 1];
			if (nu)
				nu[vp] = u[si + i + 1];
			ni[vp] = vp;
			vp++;
		}
	}
	free(m->vertices);
	m->vertices = nv;
	m->normals = nn;
	m->uvs = nu;
	m->indices = ni;
}

bool	parse_fbx_ascii(const char *path, t_scene *scene)
{
	char			*l;
	t_skinned_mesh	m;
	t_vec3			*rn;
	t_vec2			*ru;
	int				fd;
	int				*ri;
	int				rc;
	int				vc;
	int				nc;
	int				uc;

	rn = NULL;
	ru = NULL;
	rc = 0;
	vc = 0;
	nc = 0;
	uc = 0;
	if ((fd = open(path, O_RDONLY)) < 0)
		return (false);
	ft_memset(&m, 0, sizeof(t_skinned_mesh));
	m.base.name = ft_strdup(path);
	if (!(l = find_node(fd, "Vertices:")))
		return (close(fd), false);
	free(l);
	m.base.vertices = parse_vec3(fd, &vc);
	if (!(l = find_node(fd, "PolygonVertexIndex:")))
		return (close(fd), false);
	free(l);
	ri = parse_indices(fd, &rc);
	if ((l = find_node(fd, "Normals:")))
	{
		free(l);
		rn = parse_vec3(fd, &nc);
	}
	if ((l = find_node(fd, "UV:")))
	{
		free(l);
		ru = parse_vec2(fd, &uc);
	}
	close(fd);
	if (!m.base.vertices || !ri)
		return (false);
	build_flat(&m.base, ri, rc, rn, ru);
	if (rn)
		free(rn);
	if (ru)
		free(ru);
	free(ri);
	m.vertex_count = m.base.tri_count * 3;
	mesh_build_bvh(&m.base);
	printf("FBX ASCII Loaded: %s (%d tris)\n", path, m.base.tri_count);
	return (scene_add_animated(scene, m));
}
