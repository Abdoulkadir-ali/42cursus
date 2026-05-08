/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:13:14 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:56:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Performs string manipulation or inspection.
 * @note Public library exported function.
 */
int	gnl_strchr_idx(char *str, char c)
{
	char	*pos;

	if (!str)
		return (-1);
	pos = ft_strchr(str, c);
	if (!pos)
		return (-1);
	return (pos - str);
}

/**
 * @brief Executes public gnl_realloc utility.
 * @note Public library exported function.
 */
char	*gnl_realloc(char *s1, char *s2)
{
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (s1);
	res = ft_strjoin(s1, s2);
	free(s1);
	return (res);
}

/**
 * @brief Executes public gnl_free utility.
 * @note Public library exported function.
 */
char	*gnl_free(char **fds, int fd)
{
	if (fds[fd])
	{
		free(fds[fd]);
		fds[fd] = NULL;
	}
	return (NULL);
}
