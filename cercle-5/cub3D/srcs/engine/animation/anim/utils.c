/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:58:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/05 23:35:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

char	*anim_get_dirname(const char *path)
{
	char		*res;
	const char	*end;
	size_t		len;

	if (!path)
		return (NULL);
	end = path + ft_strlen(path);
	while (end > path && *(end - 1) == '/')
		end--;
	while (end > path && *(end - 1) != '/')
		end--;
	if (end == path)
		return (ft_strdup("."));
	if (end == path + 1)
		return (ft_strdup("/"));
	len = end - path;
	res = malloc(len + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, path, len + 1);
	return (res);
}

char	*anim_join_path(const char *dir, const char *file)
{
	char	*res;
	size_t	len;

	if (!dir || !file)
		return (NULL);
	len = ft_strlen(dir) + ft_strlen(file) + 2;
	res = malloc(len);
	if (!res)
		return (NULL);
	ft_strlcpy(res, dir, len);
	ft_strlcat(res, "/", len);
	ft_strlcat(res, file, len);
	return (res);
}

int	anim_grow_clip_capacity(t_anim_clip *clip, size_t min_capacity)
{
	unsigned int	**next;
	size_t			new_capacity;

	if (!clip)
		return (0);
	new_capacity = clip->frame_capacity;
	if (new_capacity == 0)
		new_capacity = 8;
	while (new_capacity < min_capacity)
		new_capacity *= 2;
	next = malloc(sizeof(unsigned int *) * new_capacity);
	if (!next)
		return (0);
	if (clip->frames)
	{
		ft_memcpy(next, clip->frames,
			sizeof(unsigned int *) * clip->frame_count);
		free(clip->frames);
	}
	clip->frames = next;
	clip->frame_capacity = new_capacity;
	return (1);
}

int	parse_meta(t_anim_clip *clip, char *line)
{
	char	name[256];
	int		val;

	if (!parse_anim_config(line, name, &val))
		return (0);
	if (ft_strcmp(name, "original_fps") == 0)
	{
		if (val > 0)
		{
			clip->original_fps = val;
			clip->frame_duration_us = 1000000 / clip->original_fps;
		}
		return (1);
	}
	if (ft_strcmp(name, "offset_x") == 0)
	{
		clip->offset.x = val;
		return (1);
	}
	if (ft_strcmp(name, "offset_y") == 0)
	{
		clip->offset.y = val;
		return (1);
	}
	return (2);
}

int	parse_anim_config(char *line, char *token, int *count)
{
	char	*sep;
	size_t	len;

	if (!line || !*line)
		return (0);
	sep = line;
	while (*sep && *sep != ' ' && *sep != '\t' && *sep != '\n')
		sep++;
	len = (size_t)(sep - line);
	if (len == 0 || len >= 256)
		return (0);
	ft_strlcpy(token, line, len + 1);
	while (*sep == ' ' || *sep == '\t')
		sep++;
	*count = ft_atoi(sep);
	return (1);
}
