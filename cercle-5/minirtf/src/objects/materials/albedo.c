/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   albedo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 03:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:11:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "material.h"

t_vec3	material_albedo(const t_app *app, const t_material *m, float u,
			float v, float dist)
{
	t_vec3	tc;
	float	lod;

	if (!m || m->tex_id < 0 || (size_t)m->tex_id >= app->scene.n_textures)
		return (m ? m->albedo : v3(1, 1, 1));
	lod = 0.0f;
	if (app->set.anim.use_mips)
		lod = log2f(fmaxf(1.0f, dist * 0.05f)) + app->set.anim.mip_bias;
	tc = texture_sample(&app->scene.textures[m->tex_id], u, v, lod);
	return (v3_hmul(m->albedo, tc));
}
