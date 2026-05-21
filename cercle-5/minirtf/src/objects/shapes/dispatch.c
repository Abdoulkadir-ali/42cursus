/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:24:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 02:24:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"

int	dispatch(char **t, int n, t_app *app)
{
	t_scene	*s;

	s = &app->scene;
	if (!strcmp(t[0], "A"))
		return (parse_ambient(t, n, s));
	if (!strcmp(t[0], "C"))
		return (parse_camera(t, n, s));
	if (!strcmp(t[0], "L"))
		return (parse_light(t, n, s));
	if (!strcmp(t[0], "sp"))
		return (parse_sphere(t, n, s));
	if (!strcmp(t[0], "pl"))
		return (parse_plane(t, n, s));
	if (!strcmp(t[0], "cy"))
		return (parse_cylinder(t, n, s));
	if (!strcmp(t[0], "bx"))
		return (parse_box(t, n, s));
	if (!strcmp(t[0], "ca"))
		return (parse_capsule(t, n, s));
	if (!strcmp(t[0], "py"))
		return (parse_pyramid(t, n, s));
	if (!strcmp(t[0], "tr"))
		return (parse_triangle(t, n, s));
	if (!strcmp(t[0], "fdf"))
		return (parse_fdf(t, n, s));
	if (!strcmp(t[0], "glb"))
		return (parse_glb(t, n, s));
	if (!strcmp(t[0], "bh") || !strcmp(t[0], "bhole"))
		return (parse_blackhole(t, n, s));
	if (!strcmp(t[0], "g") || !strcmp(t[0], "grav"))
		return (parse_gravity(t, n, s));
	if (!strcmp(t[0], "G"))
		return (parse_g_const(t, n, s));
	if (!strcmp(t[0], "damp"))
		return (parse_damp(t, n, s));
	if (!strcmp(t[0], "phys"))
		return (parse_phys(t, n, s));
	if (!strcmp(t[0], "mass"))
		return (parse_mass(t, n, s));
	if (!strcmp(t[0], "vel"))
		return (parse_vel(t, n, s));
	if (!strcmp(t[0], "pe"))
		return (parse_pe(t, n, s));
	if (!strcmp(t[0], "sb"))
		return (parse_sb(t, n, s));
	if (!strcmp(t[0], "rc"))
		return (parse_rect_quad(t, n, s));
	if (!strcmp(t[0], "re"))
		return (parse_rect_planar(t, n, s));
	if (!strcmp(t[0], "dyn"))
		return (parse_dyn(t, n, s, &app->phys));
	return (parse_property(t, n, s));
}
