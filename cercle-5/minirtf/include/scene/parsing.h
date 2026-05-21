/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 02:24:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:54:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "io.h"
# include "scene.h"

struct s_app;
struct s_phys_world;

int	push_tri(t_scene *s, t_vec3 a, t_vec3 b, t_vec3 c, t_vec3 col);
int		dispatch(char **t, int n, struct s_app *app);
int		parse_property(char **t, int n, t_scene *s);
int		parse_ambient(char **t, int n, t_scene *s);
int		parse_camera(char **t, int n, t_scene *s);
int		parse_light(char **t, int n, t_scene *s);
int		parse_sphere(char **t, int n, t_scene *s);
int		parse_plane(char **t, int n, t_scene *s);
int		parse_cylinder(char **t, int n, t_scene *s);
int		parse_box(char **t, int n, t_scene *s);
int		parse_capsule(char **t, int n, t_scene *s);
int		parse_pyramid(char **t, int n, t_scene *s);
int		parse_triangle(char **t, int n, t_scene *s);
int		parse_fdf(char **t, int n, t_scene *s);
int		parse_glb(char **t, int n, t_scene *s);
int		parse_blackhole(char **t, int n, t_scene *s);
int		parse_bhole(char **t, int n, t_scene *s);
int		parse_gravity(char **t, int n, t_scene *s);
int		parse_g_const(char **t, int n, t_scene *s);
int		parse_damp(char **t, int n, t_scene *s);
int		parse_phys(char **t, int n, t_scene *s);
int		parse_mass(char **t, int n, t_scene *s);
int		parse_vel(char **t, int n, t_scene *s);
int		parse_pe(char **t, int n, t_scene *s);
int		parse_sb(char **t, int n, t_scene *s);
int		parse_rect_quad(char **t, int n, t_scene *s);
int		parse_rect_planar(char **t, int n, t_scene *s);
int		parse_dyn(char **t, int n, t_scene *s, struct s_phys_world *w);

#endif
