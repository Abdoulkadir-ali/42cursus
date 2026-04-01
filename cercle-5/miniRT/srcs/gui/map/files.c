/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   current.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 16:20:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static bool	is_rt_file(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strcmp(filename + len - 3, ".rt") == 0);
}

static t_map_entry	*create_node(const char *name)
{
	t_map_entry	*node;

	node = malloc(sizeof(t_map_entry));
	if (!node)
		return (NULL);
	ft_memset(node, 0, sizeof(*node));
	node->path = ft_strjoin("maps/rt/", name);
	if (!node->path)
	{
		free(node);
		return (NULL);
	}
	return (node);
}

static void	add_map_node(t_gui *gui, t_map_entry ***tail, const char *name)
{
	t_map_entry	*node;

	node = create_node(name);
	if (node)
	{
		**tail = node;
		*tail = &node->next;
		gui->map_info.count++;
	}
}

void	fill_map_list(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*entry;
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
			add_map_node(gui, &tail, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}
