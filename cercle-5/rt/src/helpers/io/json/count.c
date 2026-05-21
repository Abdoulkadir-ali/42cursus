/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:25:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:25:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	json_count_array(const char *p, const char *end)
{
	int	n;

	p = json_skip_ws(p, end);
	if (p >= end || *p != '[')
		return (0);
	p++;
	p = json_skip_ws(p, end);
	if (p < end && *p == ']')
		return (0);
	n = 0;
	while (p < end)
	{
		n++;
		p = json_skip_value(p, end);
		p = json_skip_ws(p, end);
		if (p >= end || *p != ',')
			break ;
		p++;
	}
	return (n);
}
