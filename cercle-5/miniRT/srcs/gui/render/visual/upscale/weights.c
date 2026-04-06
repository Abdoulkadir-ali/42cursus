/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 03:06:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_weights(float w[4], float fx, float fy, float *db[2])
{
	float	d00;

	w[0] = (1.0f - fx) * (1.0f - fy);
	w[1] = fx * (1.0f - fy);
	w[2] = (1.0f - fx) * fy;
	w[3] = fx * fy;
	if (db[0])
	{
		d00 = db[0][0];
		if (d00 > 1e-4f)
		{
			if (fabsf(db[0][1] - d00) / d00 > DEPTH_THRESH)
				w[1] = 0.0f;
			if (fabsf(db[1][0] - d00) / d00 > DEPTH_THRESH)
				w[2] = 0.0f;
			if (fabsf(db[1][1] - d00) / d00 > DEPTH_THRESH)
				w[3] = 0.0f;
		}
	}
}
