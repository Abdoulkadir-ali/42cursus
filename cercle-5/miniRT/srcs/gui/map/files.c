/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 16:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"
#include <dirent.h>

static bool	is_rt_file(const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 4)
		return (false);
	return (ft_strcmp(name + len - 3, ".rt") == 0);
}

/*
** Extracts the directory component of path (everything before the last /).
** Returns a heap-allocated string; caller must free.
*/
static char	*extract_folder(const char *path)
{
	const char	*sep;

	sep = ft_strrchr(path, '/');
	if (!sep)
		return (ft_strdup("."));
	return (ft_substr(path, 0, (size_t)(sep - path)));
}

static t_map_entry	*create_node(const char *folder, const char *name)
{
	t_map_entry	*node;
	char		*tmp;
	size_t		len;

	node = ft_calloc(1, sizeof(t_map_entry));
	if (!node)
		return (NULL);
	len = ft_strlen(folder);
	if (len > 0 && folder[len - 1] == '/')
		node->path = ft_strjoin(folder, name);
	else
	{
		tmp = ft_strjoin(folder, "/");
		node->path = ft_strjoin(tmp, name);
		free(tmp);
	}
	if (!node->path)
		return (free(node), NULL);
	return (node);
}

static void	add_map_node(t_gui *gui, t_map_entry ***tail,
					const char *folder, const char *name)
{
	t_map_entry	*node;

	node = create_node(folder, name);
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
	char			*folder;

	folder = extract_folder(gui->scene->name);
	if (!folder)
		return ;
	dir = opendir(folder);
	if (!dir)
	{
		free(folder);
		return ;
	}
	tail = &gui->map_info.head;
	gui->map_info.count = 0;
	entry = readdir(dir);
	while (entry)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
			add_map_node(gui, &tail, folder, entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
	free(folder);
}
