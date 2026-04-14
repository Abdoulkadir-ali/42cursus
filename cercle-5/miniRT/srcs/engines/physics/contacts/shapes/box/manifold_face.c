/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manifold_face.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 09:42:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/**
 * @brief Fills ax[3] (right/up/forward) and he[3] (half-extents) for a box.
 */
static void	fill_box_basis(t_box *bx, t_vec3 ax[3], double he[3])
{
	ax[0] = bx->transform.right;
	ax[1] = bx->transform.up;
	ax[2] = bx->transform.forward;
	he[0] = bx->half_extents.x;
	he[1] = bx->half_extents.y;
	he[2] = bx->half_extents.z;
}

/**
 * @brief Given face center and two scaled tangent vectors, fill the 4 corners.
 *        e0 and e1 are already scaled by their respective half-extents.
 */
static void	fill_face_corners(t_vec3 fc, t_vec3 e0, t_vec3 e1, t_vec3 v[4])
{
	v[0] = vec3_add(vec3_add(fc, e0), e1);
	v[1] = vec3_add(vec3_sub(fc, e0), e1);
	v[2] = vec3_sub(vec3_sub(fc, e0), e1);
	v[3] = vec3_sub(vec3_add(fc, e0), e1);
}

/**
 * @brief Finds the axis index of ax[3] most aligned with dir.
 *        Sets *sgn to +1 if aligned, -1 if anti-aligned.
 */
static int	find_best_axis(t_vec3 ax[3], t_vec3 dir, int *sgn)
{
	double	d;
	double	best_d;
	int		best;
	int		i;

	best = 0;
	best_d = -1e30;
	i = 0;
	while (i < 3)
	{
		d = vec3_dot(ax[i], dir);
		if (fabs(d) > best_d)
		{
			best_d = fabs(d);
			best = i;
		}
		i++;
	}
	*sgn = 1;
	if (vec3_dot(ax[best], dir) < 0.0)
		*sgn = -1;
	return (best);
}

/**
 * @brief Returns the outward face normal and fills verts[4] with the
 *        world-space corners of the face on bx most aligned with dir.
 *        Used to find the reference face (A) and incident face (B) for
 *        contact manifold generation.
 */
t_vec3	best_box_face_verts(t_box *bx, t_vec3 dir, t_vec3 verts[4])
{
	t_vec3	ax[3];
	double	he[3];
	int		best;
	int		sgn;
	t_vec3	fc;

	fill_box_basis(bx, ax, he);
	best = find_best_axis(ax, dir, &sgn);
	fc = vec3_add(bx->phys.center,
			vec3_scale(vec3_scale(ax[best], (double)sgn), he[best]));
	fill_face_corners(fc,
		vec3_scale(ax[(best + 1) % 3], he[(best + 1) % 3]),
		vec3_scale(ax[(best + 2) % 3], he[(best + 2) % 3]),
		verts);
	return (vec3_scale(ax[best], (double)sgn));
}
