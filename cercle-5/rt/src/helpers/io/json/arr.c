/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:25:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:25:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

const char	*json_arr_get(const char *p, const char *end, int n)
{
	int	i;

	p = json_skip_ws(p, end);
	if (p >= end || *p != '[')
		return (NULL);
	p++;
	i = 0;
	while (p < end)
	{
		p = json_skip_ws(p, end);
		if (p >= end || *p == ']')
			return (NULL);
		if (i == n)
			return (p);
		p = json_skip_value(p, end);
		p = json_skip_ws(p, end);
		if (p < end && *p == ',')
			p++;
		i++;
	}
	return (NULL);
}
