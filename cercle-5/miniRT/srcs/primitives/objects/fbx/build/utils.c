/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 03:15:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/09 03:15:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fbx.h"

static int	fbx_count_poly_tris(int *raw, size_t *ps, size_t raw_c)
{
	int	vn;
	int	idx;

	vn = 0;
	while (*ps < raw_c)
	{
		idx = raw[(*ps)++];
		vn++;
		if (idx < 0)
			break ;
	}
	if (vn >= 3)
		return (vn - 2);
	return (0);
}

size_t	fbx_count_tris(int *raw, size_t raw_c)
{
	size_t	ps;
	int		tc;

	ps = 0;
	tc = 0;
	while (ps < raw_c)
		tc += fbx_count_poly_tris(raw, &ps, raw_c);
	ft_print_debug("[COUNT_TRIS] result tc=%d\n", tc);
	return (tc);
}
