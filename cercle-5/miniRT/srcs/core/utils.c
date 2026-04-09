/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 18:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include <sys/stat.h>
#include <dirent.h>

bool	is_rt_file(const char *name)
{
	size_t	len;

	len = ft_strlen(name);
	if (len < 4)
		return (false);
	return (ft_strcmp(name + len - 3, ".rt") == 0);
}

bool	is_directory(const char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (false);
	return (S_ISDIR(st.st_mode));
}

static char	*build_path(const char *dir, const char *name)
{
	char	*tmp;
	char	*result;
	size_t	len;

	len = ft_strlen(dir);
	if (len > 0 && dir[len - 1] == '/')
		return (ft_strjoin(dir, name));
	tmp = ft_strjoin(dir, "/");
	result = ft_strjoin(tmp, name);
	free(tmp);
	return (result);
}

char	*first_rt_in_dir(const char *dir)
{
	DIR				*d;
	struct dirent	*entry;
	char			*result;

	d = opendir(dir);
	if (!d)
		return (NULL);
	result = NULL;
	entry = readdir(d);
	while (entry && !result)
	{
		if (entry->d_type == DT_REG && is_rt_file(entry->d_name))
			result = build_path(dir, entry->d_name);
		entry = readdir(d);
	}
	closedir(d);
	return (result);
}
