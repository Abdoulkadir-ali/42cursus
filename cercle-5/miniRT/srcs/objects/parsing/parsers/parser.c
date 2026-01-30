/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:59:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 17:15:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_line(char *line)
{
	t_nodes			*av_nodes;
	t_object_validator	*v;
	int					i;

	av_nodes = ft_split_nodes(line, " ", &any_match);
	if (!av_nodes || !av_nodes->content)
		return (NULL);
	v = get_validator();
	i = 0;
	while (v[i].id)
	{
		if (ft_strcmp((char *)av_nodes->content, v[i].id) == 0)
		{
			if (!validate_line_nodes(av_nodes->next, v[i].format))
			{
				ft_lstclear(&av_nodes, free);
				return (NULL);
			}
			ft_lstclear(&av_nodes, free);
			if (v[i].type == AMBIENT)
				return (parse_ambient(line));
			if (v[i].type == CAMERA)
				return (parse_camera(line));
			if (v[i].type == LIGHT)
				return (parse_light(line));
			if (v[i].type == SPHERE)
				return (parse_sphere(line));
			if (v[i].type == PLANE)
				return (parse_plane(line));
			if (v[i].type == SQUARE)
				return (parse_square(line));
			if (v[i].type == CYLINDER)
				return (parse_cylinder(line));
		}
		i++;
	}
	ft_lstclear(&av_nodes, free);
	return (NULL);
}

t_nodes	*parse_lines(char *filepath)
{
	int		fd;
	char	*line;
	t_nodes	*lst;
	t_nodes	*new_node;

	lst = NULL;
	fd = open(filepath, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (*line != '\n' && *line != '#')
		{
			new_node = ft_lstnew(parse_line(line));
			if (!new_node || !new_node->content)
				return (ft_lstclear(&lst, &destroy_object), free(line), NULL);
			ft_lstadd_back(&lst, new_node);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (lst);
}
