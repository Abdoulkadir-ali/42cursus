/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:11:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 19:20:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H

# include "physics.h"
# include "objects.h"

typedef struct s_collision
{
	t_vec3	normal;
	double	pen;
	double	min_dist_sq;
	bool	hit;
	t_vec3	best_normal;
	double	best_pen;
}	t_collision;

/* Internal collision helpers */
bool	mesh_aabb_overlap(const t_aabb *a, const t_aabb *b);
bool	test_sphere_triangle(const struct s_sphere *s, t_vec3 v[3],
			t_collision *col);
t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2);
bool	detect_sphere_capsule_collision(const struct s_sphere *s,
			const t_collider *c, t_vec3 *out_normal, double *out_penetration);

#endif
