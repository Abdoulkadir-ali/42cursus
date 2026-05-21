/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:25:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:36:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

static const char	*json_skip_key(const char *p, const char *end)
{
	if (p >= end || *p != '"')
		return (NULL);
	p++;
	while (p < end && *p != '"')
	{
		if (*p == '\\' && p + 1 < end)
			p++;
		p++;
	}
	if (p >= end)
		return (NULL);
	return (p);
}

static const char	*json_check_key(const char *p, const char *q,
						const char *end, const char *key)
{
	size_t	klen;

	klen = strlen(key);
	if ((size_t)(q - p - 1) == klen && strncmp(p + 1, key, klen) == 0)
	{
		p = q + 1;
		p = json_skip_ws(p, end);
		if (p < end && *p == ':')
			p++;
		return (json_skip_ws(p, end));
	}
	return (NULL);
}

static const char	*json_step_obj(const char *p, const char *end)
{
	p = json_skip_ws(p, end);
	if (p < end && *p == ':')
		p++;
	p = json_skip_value(p, end);
	p = json_skip_ws(p, end);
	if (p < end && *p == ',')
		p++;
	return (p);
}

const char	*json_obj_find(const char *p, const char *end, const char *key)
{
	const char	*q;
	const char	*res;

	p = json_skip_ws(p, end);
	if (p >= end || *p != '{')
		return (NULL);
	p++;
	while (p < end && *p != '}')
	{
		p = json_skip_ws(p, end);
		if (p >= end || *p == '}')
			break ;
		q = json_skip_key(p, end);
		if (!q)
			return (NULL);
		res = json_check_key(p, q, end, key);
		if (res)
			return (res);
		p = json_step_obj(q + 1, end);
	}
	return (NULL);
}
