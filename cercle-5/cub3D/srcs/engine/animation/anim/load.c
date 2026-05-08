/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:58:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 01:55:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

static int	load_frame_data(t_anim_clip *clp, char *path, t_texture *tmp)
{
	unsigned int	*prev;
	bool			is_delta;

	prev = NULL;
	if (clp->frame_count > 0)
		prev = clp->frames[clp->frame_count - 1];
	is_delta = (ft_strnstr(path, ".dxpm", ft_strlen(path)) != NULL);
	if (is_delta)
		load_dxpm_manual(tmp, path, prev, NULL);
	else
		load_xpm_manual(tmp, path, NULL);
	if ((size_t)tmp->size.x < WPN_MIN_W || (size_t)tmp->size.y < WPN_MIN_H)
		safe_exit("frame too small in animation: %s", NULL, 1, path);
	if (clp->frame_count > 0 && ((size_t)tmp->size.x != (size_t)clp->size.x
			|| (size_t)tmp->size.y != (size_t)clp->size.y))
		safe_exit("frame size mismatch in animation: %s", NULL, 1, path);
	return (1);
}

static int	dup_frame_to_clip(t_anim_clip *clp, t_texture *t, int count)
{
	size_t			i;
	size_t			n_px;
	unsigned int	*dup;

	n_px = (size_t)t->size.x * (size_t)t->size.y;
	i = -1;
	while (++i < (size_t)count && clp->frame_count < WPN_MAX_FRAMES)
	{
		if (i == 0)
			clp->frames[clp->frame_count++] = t->data;
		else
		{
			dup = malloc(sizeof(unsigned int) * n_px);
			if (!dup)
				return (0);
			ft_memcpy(dup, t->data, sizeof(unsigned int) * n_px);
			clp->frames[clp->frame_count++] = dup;
		}
		if (clp->frame_count == 1)
			clp->size = (t_vec2s){(int)t->size.x, (int)t->size.y};
	}
	return (1);
}

static int	load_frame(t_anim_clip *clip, char *line, char *dir)
{
	char		fname[256];
	char		*path;
	t_texture	tmp;
	int			cnt;

	cnt = 1;
	if (!parse_anim_config(line, fname, &cnt))
		return (0);
	path = anim_join_path(dir, fname);
	if (!path)
		return (0);
	ft_bzero(&tmp, sizeof(tmp));
	if (!load_frame_data(clip, path, &tmp)
		|| !anim_grow_clip_capacity(clip, clip->frame_count + (size_t)cnt)
		|| !dup_frame_to_clip(clip, &tmp, cnt))
	{
		free(path);
		return (0);
	}
	free(path);
	return (1);
}

static int	process_anim_file(t_anim_clip *cl, int fd, char *d)
{
	char	*line;
	int		res;

	while (cl->frame_count < WPN_MAX_FRAMES)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		res = parse_meta(cl, line);
		if (res == 2)
			load_frame(cl, line, d);
		free(line);
	}
	return (cl->frame_count > 0);
}

int	load_anim_clip(t_anim_clip *cl, t_window *win, const char *p, t_world *w)
{
	char	*dir;
	int		fd;
	int		ok;

	(void)win;
	(void)w;
	if (!cl || !p || (!cl->frames && !anim_init_clip(cl)))
		return (0);
	dir = anim_get_dirname(p);
	if (!dir)
		return (0);
	fd = open(p, O_RDONLY);
	if (fd < 0)
	{
		free(dir);
		safe_exit("cannot open animation file: %s", NULL, 1, p);
	}
	get_next_line_reset(fd);
	ok = process_anim_file(cl, fd, dir);
	close(fd);
	free(dir);
	if (!ok)
		safe_exit("failed to parse animation file: %s", NULL, 1, p);
	return (ok);
}
