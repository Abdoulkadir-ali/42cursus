/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 18:59:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 06:47:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_line(char *line)
{
	char				**av;
	t_object_validator	*v;
	int					i;

	av = ft_split(line, ' ');
	if (!av || !av[0])
		return (NULL);
	v = get_validator();
	i = 0;
	while (v[i].id)
	{
		if (ft_strcmp(av[0], v[i].id) == 0)
		{
			if (!validate_line(av + 1, v[i].format))
				return (free_split(av), NULL);
			return (create_object(v[i].type, av + 1));
		}
		i++;
	}
	free_split(av);
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
