/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"
#include "mesh.h"
#include "scene.h"
#include "skeletal.h"
#include <fcntl.h>
#include <unistd.h>

static int	parse_chunks(t_glb *g, unsigned char *data, size_t total)
{
	size_t			pos;
	unsigned int	len;
	unsigned int	type;

	pos = 0;
	while (pos + 8 <= total)
	{
		memcpy(&len, data + pos, 4);
		memcpy(&type, data + pos + 4, 4);
		if ((size_t)len > total - pos - 8)
			return (0);
		if (type == CHUNK_JSON)
		{
			g->json = (const char *)(data + pos + 8);
			g->jend = g->json + len;
		}
		else if (type == CHUNK_BIN)
		{
			g->bin = data + pos + 8;
			g->bin_len = len;
		}
		pos += 8 + len;
	}
	return (g->json && g->bin);
}

static int	read_glb_file(const char *path, unsigned char **out_data,
		size_t *out_len)
{
	int				fd;
	unsigned int	hdr[3];
	unsigned char	*data;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (-1);
	if (read(fd, hdr, 12) != 12 || hdr[0] != GLB_MAGIC || hdr[1] != 2
		|| hdr[2] < 12)
		return (close(fd), -1);
	data = (unsigned char *)malloc(hdr[2] - 12);
	if (!data || read(fd, data, hdr[2] - 12) != (ssize_t)(hdr[2] - 12))
	{
		close(fd);
		free(data);
		return (-1);
	}
	close(fd);
	*out_data = data;
	*out_len = hdr[2] - 12;
	return (0);
}

static void	init_glb(t_glb *g, t_scene *s, t_mesh_conf *c)
{
	memset(g, 0, sizeof(*g));
	g->scene = s;
	g->origin = c->origin;
	g->scale = (c->scale > 0.0f) ? c->scale : 1.0f;
	g->color = c->color;
	g->emit = c->emit;
	if (g->emit.x > 0.0f || g->emit.y > 0.0f || g->emit.z > 0.0f)
		g->emit_power = 1.0f;
	glb_make_rot(g->rot, c->rot);
}

static t_animator	*init_animator(const t_glb *g, int group_id)
{
	t_animator	*a;

	a = skel_animator_create();
	if (!a)
		return (NULL);
	a->pre_origin = g->origin;
	a->pre_scale = g->scale;
	memcpy(a->pre, g->rot, sizeof(float) * 9);
	a->group_id = group_id;
	return (a);
}

static void	set_group_name(t_scene *s, int gid, const char *path)
{
	const char	*nm;
	int			i;
	int			j;

	if (gid < 0 || gid >= 64)
		return ;
	nm = path;
	i = 0;
	while (path[i])
	{
		if (path[i] == '/')
			nm = path + i + 1;
		i++;
	}
	j = 0;
	while (nm[j] && j < 63)
	{
		s->group_names[gid][j] = nm[j];
		j++;
	}
	s->group_names[gid][j] = '\0';
}

static void	finalize_groups(t_scene *s, size_t base, const char *path,
		int gid)
{
	size_t	i;

	s->last_kind = 1;
	s->last_first = (int)base;
	s->last_count = (int)(s->n_bvh - base);
	if (s->last_count <= 0)
		return ;
	i = base;
	while (i < s->n_bvh)
	{
		s->bvh_objs[i].group_id = gid;
		i++;
	}
	set_group_name(s, gid, path);
}

static void	free_glb(t_glb *g, unsigned char *data)
{
	int	i;

	if (g->mats)
	{
		i = -1;
		while (++i < g->n_mats)
			(void)0;
		free(g->mats);
	}
	free(g->img_tex);
	free(data);
}

int	mesh_load_glb(t_scene *s, const char *path, t_mesh_conf *c)
{
	unsigned char	*data;
	size_t			data_len;
	t_glb			g;
	size_t			base;
	int				gid;

	if (read_glb_file(path, &data, &data_len) < 0)
		return (-1);
	init_glb(&g, s, c);
	if (!parse_chunks(&g, data, data_len))
		return (free(data), -1);
	gid = s->next_group_id++;
	g.group_id = gid;
	g.anim = init_animator(&g, gid);
	if (!g.anim)
		return (free(data), -1);
	glb_capture_nodes(&g);
	glb_capture_skins(&g);
	glb_load_materials(&g);
	base = s->n_bvh;
	g.bvh_base = (int)base;
	glb_walk_scene(&g);
	glb_capture_clips(&g);
	finalize_groups(s, base, path, gid);
	skel_animator_attach(s, g.anim);
	free_glb(&g, data);
	return (0);
}
