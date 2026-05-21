/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:26:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:26:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	json_streq(const char *p, const char *end, const char *s)
{
	size_t	n;

	p = json_skip_ws(p, end);
	if (p >= end || *p != '"')
		return (0);
	p++;
	n = strlen(s);
	if (p + n >= end)
		return (0);
	if (strncmp(p, s, n) != 0)
		return (0);
	if (p[n] == '"')
		return (1);
	return (0);
}

void	json_str_copy(const char *p, const char *end, char *dst, int max)
{
	int	n;

	p = json_skip_ws(p, end);
	if (p >= end || *p != '"')
	{
		dst[0] = 0;
		return ;
	}
	p++;
	n = 0;
	while (p < end && *p != '"' && n + 1 < max)
	{
		dst[n++] = *p++;
	}
	dst[n] = 0;
}
