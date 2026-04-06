/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:50:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/06 14:55:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "maths.h"
# include "objects.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

/* Debug print: only active when compiled with -DDEBUG or DEBUG 1 */
# if DEBUG
#  define ft_print_debug(fmt, ...) do { printf("[DEBUG] " fmt, ##__VA_ARGS__); fflush(stdout); } while (0)
# else
#  define ft_print_debug(fmt, ...) do { if (0) printf(fmt, ##__VA_ARGS__); } while (0)
# endif

/* Maths-level Debug */
void	print_vec2(t_vec2 *v);
void	print_vec3(t_vec3 *v);
void	print_mat4(t_mat4 *m);
void	print_transform(t_transform *t);
void	print_aabb(t_aabb *b);
void	print_ray(t_ray *r);
void	print_hit(t_hit *h);

/* Object Debug */
void	print_light(t_light *l);
void	print_camera(t_camera *c);
void	print_ambient(t_ambient *a);
void	print_material(t_material *m);
void	print_mesh(t_mesh *m);
void	print_obj(t_obj *c);
void	print_sphere(t_sphere *s);
void	print_plane(t_plane *p);
void	print_cylinder(t_cylinder *c);
void	print_cone(t_cone *c);

/* System Debug */
void	print_scene(t_scene *s);
void	print_bvh_node(const t_bvh *b, size_t idx, size_t depth);
void	print_bvh(t_bvh *b);
void	print_gui(t_gui *g);
void	print_parser(t_parser *p);

/* Mesh Debug */
void	debug_print_mesh_hit(const t_ray *ray, int tri_idx, double t);
void	debug_print_mesh_aabb(const t_ray *ray, double tmin, double tmax);
void	debug_print_bvh_build(size_t tri_count, size_t depth, bool start);
void	debug_print_mesh_bake(const t_mesh *mesh, bool start);
void	debug_print_triangle_test(int tri_idx, const t_vec3 *v);

/* Profiler */
void	prof_print_frame(void);

#endif
