/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

char	*fbx_next(char *p)
{
	while (*p && !ft_isdigit(*p) && *p != '-' && *p != '.' && *p != '}')
	{
		if (*p == 'a' && *(p + 1) == ':')
			p += 2;
		else
			p++;
	}
	return (p);
}

char	*find_node(char *p, char *end, const char *name)
{
	size_t	name_len;

	if (!p || !name)
		return (NULL);
	name_len = ft_strlen(name);
	while (p + name_len <= end)
	{
		if (ft_memcmp(p, (void *)name, name_len) == 0)
			return (p + name_len);
		p++;
	}
	return (NULL);
}

char	*advance_to_data(char *p, char *end)
{
	size_t	rem;
	char	*data_start;

	rem = end - p;
	if (rem > 500)
		rem = 500;
	data_start = ft_strnstr(p, "a:", rem);
	if (data_start)
		return (data_start + 2);
	return (p);
}
