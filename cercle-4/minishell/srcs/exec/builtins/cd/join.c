/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:42:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 03:15:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*join_paths(const char *a, const char *b)
{
	char	*tmp;
	char	*res;

	if (!a || a[0] == '\0')
		return (ft_strdup(b));
	if (a[0] == '/' && a[1] == '\0')
		return (ft_strjoin("/", b));
	if (a[ft_strlen(a) - 1] == '/')
		return (ft_strjoin(a, b));
	tmp = ft_strjoin(a, "/");
	res = ft_strjoin(tmp, b);
	free(tmp);
	return (res);
}
