/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poc_physic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 15:56:08 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:56:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

/* EXTERNAL DEPENDENCIES */
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>

/* NEUTRAL DEPENCIES */
# include "debug.h"
# include "defines.h"
# include "maths.h"
# include "scene.h"

/* ------------------------------------------------------------------------- */
/* CONFIGURATION & CONSTANTS                                                 */
/* ------------------------------------------------------------------------- */

# define PHYS_MAX_BODIES 2048
# define PHYS_NUM_THREADS 7
# define MAX_SUB_SHAPES 32
# define DBVT_MAX_NODES 4096
# define DBVT_MAX_LEAVES 2048

# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 10
# define BAUMGARTE 0.2
# define SLOP 0.01
# define RESTITUTION_SLOP 0.2
# define DBVT_FAT_MARGIN 0.1
# define GLOBAL_DAMPING 0.12

# define EPA_MAX_VERTS 32
# define EPA_MAX_FACES 64
# define EPA_MAX_ITER 30
# define EPA_TOL 1e-5

/* ------------------------------------------------------------------------- */
/* ENUMS                                                                     */
/* ------------------------------------------------------------------------- */

typedef enum e_phys_type
{
	TYPE_PHYS_SPHERE,
	TYPE_PHYS_BOX,
	TYPE_PHYS_CAPSULE,
	TYPE_PHYS_CYLINDER,
	TYPE_PHYS_RECT,
	TYPE_PHYS_TRI,
	TYPE_PHYS_PYRAMID,
	TYPE_PHYS_MESH
}							t_phys_type;

typedef t_vec3				(*t_support_fn)(const void *shape, t_vec3 dir);

/* ------------------------------------------------------------------------- */
/* CORE STRUCTURES                                                           */
/* ------------------------------------------------------------------------- */

typedef struct s_physics_body
{
	/* Linkage Scene (Decoupled) */
	t_transform				*transform;
	void					*shape_data;
	t_phys_type				type;
	void					*user_data;

	/* Dynamics */
	t_vec3					velocity;
	t_vec3					angular_velocity;
	t_vec3					torque;
	double					mass;
	double					inv_mass;
	t_mat3					inv_inertia;

	/* Properties */
	double					elasticity;
	double					friction;
	bool					is_static;
	bool					is_active;

	/* Compound Geometry (Lego) */
	struct					s_sub_shape
	{
		void				*shape;
		t_aabb				local_aabb;
		t_vec3				offset;
		t_mat4				transform;
		double				radius;
		t_phys_type			type;
	} sub_shapes[MAX_SUB_SHAPES];
	size_t					sub_count;
	t_aabb					global_aabb;
	t_vec3					com;
}							t_physics_body;

/* Pipeline Structures */

typedef struct s_contact
{
	t_physics_body			*a;
	t_physics_body			*b;
	t_vec3					normal;
	double					penetration;
	t_vec3					contact_point;
	t_vec3					ra;
	t_vec3					rb;
	double					impulse;
	double					restitution;
	double					friction;
}							t_contact;

typedef struct s_phys_job
{
	t_scene					*scene;
	t_contact				*out_contacts;
	int						max_contacts;
	int						found_count;
	int						thread_id;
	void					*arg;
}							t_phys_job;

/* The Physics Engine System */

typedef struct s_physics
{
	t_physics_body			bodies[PHYS_MAX_BODIES];
	int						body_count;

	t_vec3					gravity;
	double					fixed_dt;
	int						solver_iters;

	/* Thread Pool */
	pthread_t				threads[PHYS_NUM_THREADS];
	t_phys_job				jobs[PHYS_NUM_THREADS];
	sem_t					sem_start[PHYS_NUM_THREADS];
	sem_t					sem_done[PHYS_NUM_THREADS];
	int						shutdown;
	int						initialized;

	/* Broadphase Context */
	struct					s_dbvt
	{
		struct				s_dbvt_node
		{
			t_aabb			aabb;
			int left, right, leaf;
		} nodes[DBVT_MAX_NODES];
		struct				s_dbvt_leaf
		{
			t_aabb			fat;
			t_physics_body	*body;
		} leaves[DBVT_MAX_LEAVES];
		int					node_count;
		int					leaf_count;
		int					root;
	} tree;

	struct					s_static_bvh
	{
		struct				s_static_node
		{
			t_aabb			aabb;
			int left, right, obj_idx, obj_type;
		} * nodes;
		int					count;
		int					root;
	} * static_env;
}							t_physics;

/* GJK / EPA Logic Contexts */

typedef struct s_simplex
{
	t_vec3					pts;
	t_vec3					a_pts;
	t_vec3					b_pts;
	int						n;
}							t_simplex;

typedef struct s_epa_face
{
	int						idx;
	t_vec3					normal;
	double					dist;
}							t_epa_face;

typedef struct s_epa_poly
{
	t_vec3					pts[EPA_MAX_VERTS];
	t_vec3					a_pts[EPA_MAX_VERTS];
	t_vec3					b_pts[EPA_MAX_VERTS];
	int						n_verts;
	t_epa_face				faces[EPA_MAX_FACES];
	int						n_faces;
}							t_epa_poly;

typedef struct s_gjk_shape
{
	const void				*data;
	t_support_fn			support;
	t_vec3					center;
}							t_gjk_shape;

typedef struct s_edge
{
	int						a;
	int						b;
}							t_edge;

typedef struct s_body_pair
{
	t_physics_body			*a;
	t_physics_body			*b;
}							t_body_pair;

/* --- Midphase --- */
typedef struct s_shape_pair
{
	struct s_sub_shape		*sa;
	struct s_sub_shape		*sb;
	t_physics_body			*ba;
	t_physics_body			*bb;
}							t_shape_pair;

/* ------------------------------------------------------------------------- */
/* FUNCTION PROTOTYPES                                                       */
/* ------------------------------------------------------------------------- */

/* --- System API --- */
t_physics					*phys_create(void);
void						phys_destroy(t_physics *phys);
void						phys_bake_scene(t_physics *phys, t_scene *scene);
void						phys_step(t_physics *phys, t_scene *scene,
								double dt);

/* --- Lifecycle & Integration --- */
void						phys_integrate(t_physics *phys, double dt);
void						phys_integrate_bodies(t_physics *phys, double dt);
void						phys_dispatch_object(t_physics_body *b,
								t_transform *t, double dt);
void						integrate_sphere(t_sphere *sp, double dt);
void						integrate_box(t_box *bx, double dt);
void						integrate_capsule(t_capsule *cap, double dt);
void						integrate_cylinder(t_cylinder *cy, double dt);
void						integrate_rect(t_rect *rc, double dt);
void						integrate_tri(t_tri_shape *tr, double dt);
void						integrate_pyramid(t_pyramid *py, double dt);

/* --- Broadphase (DBVT & BVH) --- */
void						phys_update_broadphase(t_physics *phys);
void						build_dbvt(t_physics *phys);
int							db_query_pairs(t_physics *phys, t_body_pair *out,
								int max);
void						collect_leaves(t_physics *phys);
int							dbvt_build_range(t_physics *phys, int first,
								int count);
int							broadphase(t_physics *phys, t_body_pair *out,
								int max);
size_t						collect_bodies(t_physics *phys,
								t_physics_body **out, size_t max);
int							midphase(t_body_pair *pairs, int n,
								t_shape_pair *out, int max);

/* --- Narrowphase (GJK / EPA) --- */
bool						gjk_intersect(t_gjk_shape *a, t_gjk_shape *b,
								t_simplex *out);
bool						gjk_epa(t_gjk_shape *a, t_gjk_shape *b,
								t_simplex *s, t_vec3 *n, double *d);
t_vec3						md_support(t_gjk_shape *a, t_gjk_shape *b,
								t_vec3 dir, t_vec3 *pa, t_vec3 *pb);
void						get_contact_points(t_epa_poly *p, t_epa_face *f,
								t_vec3 *pa, t_vec3 *pb);
void						init_polytope(t_epa_poly *p, t_simplex *s);
int							closest_face(t_epa_poly *p);
void						collect_silhouette(t_epa_poly *p, t_vec3 support,
								t_edge *edges, int *n);
t_epa_face					make_face(t_epa_poly *p, int i0, int i1, int i2);
t_vec3						bary(const t_vec3 tri, t_vec3 p);

/* --- GJK Simplex Helpers --- */
bool						simplex_line(t_simplex *s, t_vec3 *dir);
bool						simplex_triangle(t_simplex *s, t_vec3 *dir);
bool						simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
void						update_simplex3(t_simplex *s, int a, int b, int c);
void						compute_ab_ao(t_simplex *s, t_vec3 *ab, t_vec3 *ao);
bool						handle_positive_simplex_line(t_vec3 ab, t_vec3 ao,
								t_vec3 *dir);
void						reduce_simplex_to_point(t_simplex *s, t_vec3 ao,
								t_vec3 *dir);

/* --- Dispatchers --- */
int							phys_detect_collisions(t_physics *phys,
								t_contact *out, int max);
int							narrow_dispatch_body_pair(t_body_pair *p,
								t_contact *contacts, int count);
int							narrow_dispatch_shape_pair(t_shape_pair *p,
								t_contact *contacts, int count);
int							gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
								t_physics_body *ba, t_physics_body *bb,
								t_transform *ta, t_transform *tb, t_contact *c);

/* --- Primitive Specific Narrowphase --- */
int							query_sphere(t_physics *phys, int idx, t_contact *c,
								int count, int max);
int							sphere_plane_contacts(t_physics *phys, t_sphere *sp,
								t_gjk_shape *sa_gjk, t_contact *c, int count,
								int max);
int							sphere_others_contacts(t_physics *phys, int idx,
								t_sphere *sp, t_aabb sa, t_gjk_shape *sa_gjk,
								t_contact *c, int count, int max);
int							traverse_bvh_contacts(t_physics *phys, int idx,
								t_sphere *sp, t_aabb saabb, t_contact *c,
								int count, int max);
bool						detect_sphere_mesh_collision(const t_sphere *sp,
								t_mesh *m, t_vec3 *n, double *p);
int							pyramid_vs_plane(t_pyramid *py, t_plane *pl,
								t_contact *c, int max_c);
int							rect_vs_plane(t_rect *rc, t_plane *pl, t_contact *c,
								int max_c);
int							tri_vs_plane(t_tri_shape *tr, t_plane *pl,
								t_contact *c, int max_c);
int							box_vs_plane(t_box *bx, t_plane *pl, t_contact *c,
								int max_c);
int							cyl_plane_contacts(t_physics *phys, t_cylinder *cy,
								t_gjk_shape *sa, t_contact *c, int count,
								int max);
int							capsule_plane_contacts(t_physics *phys,
								t_capsule *cap, t_gjk_shape *sa, t_contact *c,
								int count, int max);

/* --- GJK Support Functions --- */
t_vec3						phys_support(t_physics_body *body, t_vec3 dir);
t_vec3						gjk_support_sphere(const void *data, t_vec3 dir);
t_vec3						gjk_support_box(const void *data, t_vec3 dir);
t_vec3						gjk_support_capsule(const void *data, t_vec3 dir);
t_vec3						gjk_support_cylinder(const void *data, t_vec3 dir);
t_vec3						gjk_support_rect(const void *data, t_vec3 dir);
t_vec3						gjk_support_tri(const void *data, t_vec3 dir);
t_vec3						gjk_support_pyramid(const void *data, t_vec3 dir);
t_vec3						gjk_support_mesh(const void *data, t_vec3 dir);
t_vec3						gjk_support_list(const t_vec3 *v, int count,
								t_vec3 dir);

/* --- Solver --- */
void						phys_solve(t_physics *phys, t_contact *contacts,
								int count);
void						solve_velocities(t_contact *contacts, int count);
void						solve_positions(t_contact *contacts, int count);
void						apply_torque(t_contact *c, t_physics_body *body,
								double impulse);
void						apply_solver_torque(t_physics_body *b, t_vec3 r,
								t_vec3 imp, double inv_m, double s);
t_vec3						point_vel(t_physics_body *b, t_vec3 r);
double						ang_term(t_physics_body *b, t_vec3 r, t_vec3 n,
								double inv_m);
void						apply_friction(t_contact *ct, double inv_a,
								double inv_b, t_vec3 rv);

/* --- AABB & Geometry Helpers --- */
void						phys_update_body_aabb(t_physics_body *b);
t_aabb						compute_global_aabb(t_physics_body *b);
void						compute_mesh_aabb(t_mesh *mesh, t_aabb *out);
void						compute_primitive_aabb(t_physics_body *b);
bool						aabb_overlap_broad(t_aabb a, t_aabb b);
bool						aabb_overlap_local(t_aabb a, t_aabb b);
t_aabb						sphere_aabb(t_sphere *sp);
t_aabb						box_aabb(t_box *bx);
t_aabb						capsule_aabb(t_capsule *cp);
t_aabb						cylinder_aabb(t_cylinder *cy);
t_aabb						rect_aabb(t_rect *rc);
t_aabb						tri_aabb(t_tri_shape *tr);
t_aabb						pyramid_aabb(t_pyramid *py);

/* --- Compound Body (Lego) --- */
void						init_compound(t_physics_body *b, void *bricks,
								size_t n);
void						update_compound(t_physics_body *b);
void						compute_com(t_physics_body *b);
void						compute_inertia(t_physics_body *b);

/* --- Interaction & Tools --- */
void						phys_apply_impulse(t_physics_body *body,
								t_vec3 impulse, t_vec3 point);
void						phys_shoot_force(t_physics *phys, t_ray ray,
								double power);
void						phys_resolve_ccd(t_physics *phys, t_physics_body *b,
								double dt);
void						phys_debug_spheres(t_physics *phys);
t_vec3						gravity_vec(void);
double						clamp_d(double v, double lo, double hi);
t_vec3						rot_by_ang(t_vec3 a, t_vec3 rot, double dt);

#endif