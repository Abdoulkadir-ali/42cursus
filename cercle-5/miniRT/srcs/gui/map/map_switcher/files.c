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

int	count_maps(void)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir("maps/rt");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

void	fill_map_list(t_gui *gui)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir("maps/rt");
	if (!dir)
		return ;
	gui->map_info.count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
		{
			gui->map_info.files[gui->map_info.count]
				= ft_strjoin("maps/rt/", entry->d_name);
			if (gui->map_info.files[gui->map_info.count])
				gui->map_info.count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
}
