/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Minimal JSON parser helper to find a key.
 */
char	*json_find_key(char *json, const char *key)
{
	char	*ptr;
	size_t	len;

	if (!json || !key)
		return (NULL);
	len = ft_strlen(key);
	ptr = json;
	while (*ptr)
	{
		ptr = ft_strnstr(ptr, key, ft_strlen(ptr));
		if (!ptr)
			return (NULL);
		if (ptr > json && *(ptr - 1) == '"' && *(ptr + len) == '"')
			return (ptr + len + 1);
		ptr++;
	}
	return (NULL);
}

/**
 * Minimal JSON parser helper to get an integer value.
 */
int	json_get_int(char *json, const char *key)
{
	char	*ptr;

	if (!json || !key)
		return (-1);
	ptr = json_find_key(json, key);
	if (!ptr)
		return (-1);
	while (*ptr && (*ptr == ':' || *ptr == ' ' || *ptr == '"'))
		ptr++;
	return (ft_atoi(ptr));
}
