/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   property.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:12:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:03:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPERTY_H
# define PROPERTY_H

# include "scene.h"

/**
 * @brief Decouples UI from DOD storage layout.
 * Each property maps a UI name/range to a pair of getter/setter functions
 * that operate on the t_scene SoA arrays.
 */
typedef struct s_property
{
	const char	*name;
	double		(*get)(t_scene *scene, int idx);
	void		(*set)(t_scene *scene, int idx, double val);
	double		min;
	double		max;
}				t_property;

/* Property Groups per Type */
extern const t_property	*g_props_sphere[];
extern const t_property	*g_props_plane[];
extern const t_property	*g_props_cylinder[];
extern const t_property	*g_props_cone[];
extern const t_property	*g_props_box[];
extern const t_property	*g_props_capsule[];
extern const t_property	*g_props_rect[];
extern const t_property	*g_props_pyramid[];
extern const t_property	*g_props_mesh[];
extern const t_property	*g_props_light[];
extern const t_property	*g_props_ambient[];
extern const t_property	*g_props_material[];
extern const t_property	*g_props_physics[];

/* --- PROPERTY ACCESSORS --- */

/* SoA / Primitive */
double	get_pos_x(t_scene *sc, int i);
void	set_pos_x(t_scene *sc, int i, double v);
double	get_pos_y(t_scene *sc, int i);
void	set_pos_y(t_scene *sc, int i, double v);
double	get_pos_z(t_scene *sc, int i);
void	set_pos_z(t_scene *sc, int i, double v);

double	get_axis_x(t_scene *sc, int i);
void	set_axis_x(t_scene *sc, int i, double v);
double	get_axis_y(t_scene *sc, int i);
void	set_axis_y(t_scene *sc, int i, double v);
double	get_axis_z(t_scene *sc, int i);
void	set_axis_z(t_scene *sc, int i, double v);

double	get_ext_x(t_scene *sc, int i);
void	set_ext_x(t_scene *sc, int i, double v);
double	get_ext_y(t_scene *sc, int i);
void	set_ext_y(t_scene *sc, int i, double v);
double	get_ext_z(t_scene *sc, int i);
void	set_ext_z(t_scene *sc, int i, double v);

double	get_radius(t_scene *sc, int i);
void	set_radius(t_scene *sc, int i, double v);
double	get_height(t_scene *sc, int i);
void	set_height(t_scene *sc, int i, double v);

/* Lights */
double	get_lt_bright(t_scene *sc, int i);
void	set_lt_bright(t_scene *sc, int i, double v);
double	get_lt_r(t_scene *sc, int i);
void	set_lt_r(t_scene *sc, int i, double v);
double	get_lt_g(t_scene *sc, int i);
void	set_lt_g(t_scene *sc, int i, double v);
double	get_lt_b(t_scene *sc, int i);
void	set_lt_b(t_scene *sc, int i, double v);
double	get_lt_px(t_scene *sc, int i);
void	set_lt_px(t_scene *sc, int i, double v);
double	get_lt_py(t_scene *sc, int i);
void	set_lt_py(t_scene *sc, int i, double v);
double	get_lt_pz(t_scene *sc, int i);
void	set_lt_pz(t_scene *sc, int i, double v);

/* Ambient */
double	get_amb_bright(t_scene *sc, int i);
void	set_amb_bright(t_scene *sc, int i, double v);
double	get_amb_r(t_scene *sc, int i);
void	set_amb_r(t_scene *sc, int i, double v);
double	get_amb_g(t_scene *sc, int i);
void	set_amb_g(t_scene *sc, int i, double v);
double	get_amb_b(t_scene *sc, int i);
void	set_amb_b(t_scene *sc, int i, double v);

/* Materials */
double	get_mat_rough(t_scene *sc, int i);
void	set_mat_rough(t_scene *sc, int i, double v);
double	get_mat_metal(t_scene *sc, int i);
void	set_mat_metal(t_scene *sc, int i, double v);
double	get_mat_opac(t_scene *sc, int i);
void	set_mat_opac(t_scene *sc, int i, double v);
double	get_mat_emit_r(t_scene *sc, int i);
void	set_mat_emit_r(t_scene *sc, int i, double v);
double	get_mat_emit_g(t_scene *sc, int i);
void	set_mat_emit_g(t_scene *sc, int i, double v);
double	get_mat_emit_b(t_scene *sc, int i);
void	set_mat_emit_b(t_scene *sc, int i, double v);

/* Physics */
double	get_ph_mass(t_scene *sc, int i);
void	set_ph_mass(t_scene *sc, int i, double v);
double	get_ph_elast(t_scene *sc, int i);
void	set_ph_elast(t_scene *sc, int i, double v);
double	get_ph_fric(t_scene *sc, int i);
void	set_ph_fric(t_scene *sc, int i, double v);

/* Meshes */
double	get_mesh_px(t_scene *sc, int i);
void	set_mesh_px(t_scene *sc, int i, double v);
double	get_mesh_py(t_scene *sc, int i);
void	set_mesh_py(t_scene *sc, int i, double v);
double	get_mesh_pz(t_scene *sc, int i);
void	set_mesh_pz(t_scene *sc, int i, double v);
double	get_mesh_sx(t_scene *sc, int i);
void	set_mesh_sx(t_scene *sc, int i, double v);
double	get_mesh_sy(t_scene *sc, int i);
void	set_mesh_sy(t_scene *sc, int i, double v);
double	get_mesh_sz(t_scene *sc, int i);
void	set_mesh_sz(t_scene *sc, int i, double v);

#endif
