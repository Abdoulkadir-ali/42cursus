/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 18:41:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "maths.h"
# include "scene.h"
# include "shapes.h"
# include "threads.h"
# include <stdbool.h>

typedef struct s_physics_settings
{
	float	friction;
	float	phys_substeps;
	bool	physics_on;
}			t_physics_settings;

typedef struct s_body
{
	t_vec3	pos;
	t_vec3	vel;
	t_vec3	acc;
	float	mass;
	float	inv_mass;
	float	restitution;
	float	radius_cache;
	float	temperature;
	float	temp_ambient;
	int		sphere_idx;
	int		is_static;
	int		active;
	int		sleep_frames;
}			t_body;

struct s_app;

typedef struct s_integrate_job
{
	struct s_app	*app;
	int				start;
	int				end;
	float			dt;
}	t_integrate_job;

typedef struct s_planes_job
{
	struct s_app	*app;
	int				start;
	int				end;
}	t_planes_job;

typedef struct s_pushback_job
{
	struct s_app	*app;
	int				start;
	int				end;
	int				moved;
}	t_pushback_job;

typedef struct s_phys_world
{
	t_body			*bodies;
	t_vec3			bmin;
	t_vec3			bmax;
	int				n_bodies;
	int				n;
	int				cap;
	int				enabled;
	int				paused;
	float			time_scale;
	float			cell_size;
	int				nx;
	int				ny;
	int				nz;
	int				n_cells;
	int				cells_cap;
	int				items_cap;
	int				*cell_count;
	int				*cell_start;
	int				*cell_items;
	t_integrate_job	integrate_jobs[MAX_THREADS];
	t_planes_job	planes_jobs[MAX_THREADS];
	t_pushback_job	pushback_jobs[MAX_THREADS];
}					t_phys_world;

typedef struct s_hitbox
{
	t_vec3			oc;
	float			o_a[3];
	float			d_a[3];
	const t_vec3		*ax[3];
	float			he[3];
	float			tmin;
	float			tmax;
	float			t1;
	float			t2;
	float			tmp;
	int				face;
	int				face_min;
	int				face_max;
	int				i;
	int				k;
	float			sign;
	t_vec3			n;
}					t_hitbox;
typedef struct s_cylinder_bounds
{
	t_vec3	p0;
	t_vec3	p1;
	t_vec3	e;
	t_vec3	a;
	t_vec3	lo;
	t_vec3	hi;
} 				t_cylinder_bounds;

void	phys_init(t_phys_world *w);
void	phys_free(t_phys_world *w);
void	phys_update(struct s_app *app, float dt);
void	phys_step(struct s_app *app, float dt);
int		phys_add_body(t_phys_world *w, int sphere_idx, float mass,
			float restitution, t_vec3 vel);
void	phys_ensure_all_bodies(struct s_app *app);
void	phys_apply_impulse(t_phys_world *w, int obj_idx, t_vec3 impulse);
int		phys_body_for_sphere(t_phys_world *w, int sphere_idx);
void	phys_pull_positions(t_phys_world *w, struct s_app *app);
void	phys_push_positions(t_phys_world *w, struct s_app *app);
void	phys_rebuild_body_table(struct s_app *app);
int		ray_bend_blackholes(const t_scene *s, t_ray *r);

int		build_grid(t_phys_world *w);
int		bin_bodies(t_phys_world *w, int cells);
void	resolve_pair(struct s_app *app, t_body *a, t_body *b);
void	collide_neighbors(struct s_app *app, int bi);
void	collide_planes(struct s_app *app, t_body *b);
void	collide_planes_all(struct s_app *app);
void	apply_blackhole_gravity(struct s_app *app, t_body *b, float dt);
void	integrate(struct s_app *app, float dt);
int		push_back_to_scene(struct s_app *app);

/* Bounds (primitives) */
t_aabb	sphere_bounds(const t_sphere *s);
t_aabb	cylinder_bounds(const t_cylinder *c);
t_aabb	box_bounds(const t_box *b);
t_aabb	capsule_bounds(const t_capsule *c);
t_aabb	pyramid_bounds(const t_pyramid *p);
t_aabb	triangle_bounds(const t_triangle *t);
t_aabb	object_bounds(const t_object *o);

/* Intersection */
int		hit_sphere(const t_sphere *s, const t_ray *r, t_hit *h);
int		hit_plane(const t_plane *p, const t_ray *r, t_hit *h);
int		hit_cylinder(const t_cylinder *c, const t_ray *r, t_hit *h);
int		hit_box(const t_box *b, const t_ray *r, t_hit *h);
int		hit_capsule(const t_capsule *c, const t_ray *r, t_hit *h);
int		hit_pyramid(const t_pyramid *p, const t_ray *r, t_hit *h);
int		hit_triangle(const t_triangle *t, const t_ray *r, t_hit *h);
int		hit_object(const t_object *o, const t_ray *r, t_hit *h);

/* UV mapping */
void	sphere_uv(const t_sphere *s, t_vec3 p, float *u, float *v);
void	plane_uv(const t_plane *p, t_vec3 pt, float *u, float *v);
void	cylinder_uv(const t_cylinder *c, t_vec3 p, float *u, float *v);
void	object_uv(const t_object *o, t_vec3 p, float *u, float *v);

/* Object helpers */
float	object_bsphere_radius(const t_object *o);
t_vec3	object_center(const t_object *o);
void	object_translate_to(t_object *o, t_vec3 newcenter);

#endif
