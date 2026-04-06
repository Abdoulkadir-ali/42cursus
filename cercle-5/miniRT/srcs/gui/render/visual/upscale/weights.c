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

void	get_weights(t_vec4f *w, t_vec2f f, float *db[2])
{
	float	d00;
	float	*wf;

	wf = (float *)w;
	wf[0] = (1.0f - f.x) * (1.0f - f.y);
	wf[1] = f.x * (1.0f - f.y);
	wf[2] = (1.0f - f.x) * f.y;
	wf[3] = f.x * f.y;
	if (db[0])
	{
		d00 = db[0][0];
		if (d00 > 1e-4f)
		{
			if (fabsf(db[0][1] - d00) / d00 > DEPTH_THRESH)
				wf[1] = 0.0f;
			if (fabsf(db[1][0] - d00) / d00 > DEPTH_THRESH)
				wf[2] = 0.0f;
			if (fabsf(db[1][1] - d00) / d00 > DEPTH_THRESH)
				wf[3] = 0.0f;
		}
	}
}
