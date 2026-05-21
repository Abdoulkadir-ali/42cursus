/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flt.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:26:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 18:36:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

double	json_flt(const char *p, const char *end)
{
	char	buf[48];
	int		n;

	if (!p)
		return (0.0);
	p = json_skip_ws(p, end);
	n = 0;
	while (p < end && n + 1 < (int)sizeof(buf)
		&& (*p == '-' || *p == '+' || *p == '.' || *p == 'e' || *p == 'E'
			|| (*p >= '0' && *p <= '9')))
	{
		buf[n++] = *p++;
	}
	buf[n] = 0;
	if (n == 0)
		return (0.0);
	return (strtod(buf, NULL));
}
