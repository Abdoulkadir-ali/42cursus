/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 04:50:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	camera_setup(t_camera *c, int w, int h)
{
	t_vec3	world_up;
	float	aspect;
	float	tan_half;

	c->dir = v3_norm(c->dir);
	world_up = v3(0.0f, 1.0f, 0.0f);
	if (fabsf(v3_dot(c->dir, world_up)) > 0.999f)
		world_up = v3(0.0f, 0.0f, 1.0f);
	c->right = v3_norm(v3_cross(c->dir, world_up));
	c->up = v3_cross(c->right, c->dir);
	aspect = (float)w / (float)h;
	tan_half = tanf((c->fov * 0.5f) * (float)M_PI / 180.0f);
	c->half_w = tan_half * aspect;
	c->half_h = tan_half;
}

void	camera_init_yaw_pitch(t_scene *s)
{
	t_vec3	d;

	d = v3_norm(s->cam.dir);
	s->cam_pitch = asinf(ft_clampf(d.y, -1.0f, 1.0f));
	s->cam_yaw = atan2f(d.x, d.z);
}

void	camera_from_yaw_pitch(t_camera *c, float yaw, float pitch)
{
	c->dir.x = cosf(pitch) * sinf(yaw);
	c->dir.y = sinf(pitch);
	c->dir.z = cosf(pitch) * cosf(yaw);
	c->dir = v3_norm(c->dir);
}

int	project_to_camera(const t_camera *c, t_vec3 p, int w, int h, float *sx,
		float *sy)
{
	t_vec3	cp;
	float	z;

	cp = v3_sub(p, c->pos);
	z = v3_dot(cp, c->dir);
	if (z < 0.001f)
		return (0);
	*sx = (v3_dot(cp, c->right) / (z * c->half_w) + 1.0f) * 0.5f * (float)w;
	*sy = (1.0f - v3_dot(cp, c->up) / (z * c->half_h)) * 0.5f * (float)h;
	return (*sx >= 0 && *sx < w && *sy >= 0 && *sy < h);
}
