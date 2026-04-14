/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_body_forces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 00:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

void	apply_one_body_to_sb(t_soft_body *sb, t_vec3 body_pos, double g_mass);

void	apply_vols_to_sb(t_soft_body *sb, t_scene *sc, double big_g)
{
	size_t	i;

	i = -1;
	while (++i < sc->box_count)
		if (!sc->boxes[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->boxes[i].phys.pos,
				big_g * sc->boxes[i].phys.mass);
	i = -1;
	while (++i < sc->capsule_count)
		if (!sc->capsules[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->capsules[i].phys.pos,
				big_g * sc->capsules[i].phys.mass);
	i = -1;
	while (++i < sc->cylinder_count)
		if (!sc->cylinders[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->cylinders[i].phys.pos,
				big_g * sc->cylinders[i].phys.mass);
	i = -1;
	while (++i < sc->cone_count)
		if (!sc->cones[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->cones[i].phys.pos,
				big_g * sc->cones[i].phys.mass);
}

void	apply_surfs_to_sb(t_soft_body *sb, t_scene *sc, double big_g)
{
	size_t	i;

	i = -1;
	while (++i < sc->pyramid_count)
		if (!sc->pyramids[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->pyramids[i].phys.pos,
				big_g * sc->pyramids[i].phys.mass);
	i = -1;
	while (++i < sc->rect_count)
		if (!sc->rects[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->rects[i].phys.pos,
				big_g * sc->rects[i].phys.mass);
	i = -1;
	while (++i < sc->tri_count)
		if (!sc->tris[i].phys.is_static)
			apply_one_body_to_sb(sb, sc->tris[i].phys.pos,
				big_g * sc->tris[i].phys.mass);
}
