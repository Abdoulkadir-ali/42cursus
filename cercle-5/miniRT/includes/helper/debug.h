/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2026/03/26 17:32:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 17:32:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* STD lib */
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* Standard C library */
#include "libft.h"

#ifndef DEBUG_H
# define DEBUG_H

/* External dependencies */

# ifndef DEBUG
#  define DEBUG 1
# endif

/* Debug print: only active when compiled with -DDEBUG or DEBUG 1 */
# if DEBUG
#  define ft_print_debug(...) (printf(__VA_ARGS__), fflush(stdout))
# else
#  define ft_print_debug(...) ((void)0)
# endif

/* Maths */
void	print_vec2(t_vec2 *v);
void	print_vec3(t_vec3 *v);
void	print_mat4(t_mat4 *m);
void	print_transform(t_transform *t);
void	print_aabb(t_aabb *b);

/* Objects */
void	print_sphere(t_sphere *s);
void	print_plane(t_plane *p);
void	print_cylinder(t_cylinder *c);
void	print_cone(t_cone *c);
void	print_light(t_light *l);
void	print_camera(t_camera *c);
void	print_ambient(t_ambient *a);
void	print_material(t_material *m);
void	print_mesh(t_mesh *m);
void	print_obj_ctx(t_obj_ctx *c);

/* System */
void	print_scene(t_scene *s);
void	print_ray(t_ray *r);
void	print_hit(t_hit *h);
void	print_parser(t_parser *p);
void	print_gui(t_gui *g);
void	print_bvh_node(const t_bvh *b, int idx, int depth);
void	print_bvh(t_bvh *b);

/* Mesh Specific Debug */
void	debug_print_mesh_hit(const t_ray *ray, int tri_idx, double t);
void	debug_print_mesh_aabb(const t_ray *ray, double tmin, double tmax);
void	debug_print_bvh_build(int tri_count, int depth, bool start);
void	debug_print_mesh_bake(const t_mesh *mesh, bool start);
void	debug_print_triangle_test(int tri_idx, const t_vec3 *v);

#endif
