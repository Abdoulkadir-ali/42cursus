/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

static bool	is_rt_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

void	fill_map_list(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*entry;
	t_map_entry		*node;
	t_map_entry		**tail;

	dir = opendir("maps/rt");
	if (!dir)
		return ;
	tail = &gui->map_info.head;
	gui->map_info.count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
		{
			node = malloc(sizeof(t_map_entry));
			if (node)
			{
				ft_memset(node, 0, sizeof(*node));
				node->path = ft_strjoin("maps/rt/", entry->d_name);
				if (node->path)
				{
					*tail = node;
					tail = &node->next;
					gui->map_info.count++;
				}
				else
					free(node);
			}
		}
		entry = readdir(dir);
	}
	closedir(dir);
}
