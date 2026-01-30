/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:13:32 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:13:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

static void	strip_newline(char *s)
{
	if (!s)
		return ;
	if (s[strlen(s) - 1] == '\n')
		s[strlen(s) - 1] = '\0';
}

t_scene	*scene_load_from_file(const char *path)
{
	int fd;
	char *line;
	t_scene *scene;
	t_object *obj;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (NULL);
	}
	scene = create_scene(path);
	if (!scene)
	{
		close(fd);
		return (NULL);
	}
	while ((line = get_next_line(fd)))
	{
		strip_newline(line);
		if (*line == '\0')
		{
			free(line);
			continue ;
		}
		obj = parse_line(line);
		free(line);
		if (!obj)
			continue ;
		if (!scene_add_object(scene, obj))
		{
			destroy_object(obj);
			destroy_scene(scene);
			close(fd);
			return (NULL);
		}
	}
	close(fd);
	return (scene);
}