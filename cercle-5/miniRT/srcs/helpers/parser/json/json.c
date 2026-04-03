/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:12:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_json_value	*json_parse(const char *json_str)
{
	const char	*s;

	s = json_str;
	return (json_parse_inner_value(&s));
}

t_json_value	*json_parse_len(const char *json_str, size_t len)
{
	char			*buf;
	t_json_value	*result;

	buf = ft_strndup(json_str, len);
	if (!buf)
		return (NULL);
	result = json_parse(buf);
	free(buf);
	return (result);
}
