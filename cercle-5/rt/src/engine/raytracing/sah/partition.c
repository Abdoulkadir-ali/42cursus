/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   partition.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:55:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 00:55:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

size_t	partition_idx(t_sah s, int best)
{
	size_t	i;
	size_t	j;
	size_t	tmp;
	int		b;

	i = 0;
	j = s.n - 1;
	while (i <= j)
	{
		b = (int)((axis_val(s.centers[s.idx[i]], s.axis) - s.bmin) * s.k);
		if (b < 0)
			b = 0;
		if (b >= SAH_BINS)
			b = SAH_BINS - 1;
		if (b <= best)
			i++;
		else
		{
			tmp = s.idx[i];
			s.idx[i] = s.idx[j];
			s.idx[j--] = tmp;
		}
	}
	return (i);
}
