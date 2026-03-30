/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 13:47:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 13:47:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "libft.h"
#include <stddef.h>

/* Extract directory part from a filepath. */
char	*path_get_dir(const char *filepath)
{
	char	*slash;
	char	*dir;
	size_t	len;

	if (!filepath)
		return (NULL);
	slash = ft_strrchr(filepath, '/');
	if (slash)
	{
		len = slash - filepath + 1;
		dir = ft_substr(filepath, 0, len);
	}
	else
	{
		dir = ft_strdup("./");
	}
	return (dir);
}
