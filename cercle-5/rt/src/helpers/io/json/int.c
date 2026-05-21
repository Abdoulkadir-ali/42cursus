/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:36:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

long	json_int(const char *p, const char *end)
{
	long	v;
	int		neg;

	v = 0;
	neg = 0;
	if (!p)
		return (0);
	p = json_skip_ws(p, end);
	if (p < end && *p == '-')
	{
		neg = 1;
		p++;
	}
	while (p < end && *p >= '0' && *p <= '9')
	{
		v = v * 10 + (*p - '0');
		p++;
	}
	if (neg)
		return (-v);
	return (v);
}
