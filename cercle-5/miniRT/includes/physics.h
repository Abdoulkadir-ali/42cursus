/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:26:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:09:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

/* External dependencies */
# include "defines.h"
# include "maths.h"
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <string.h>

/* Constants */
# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01
# define RESTITUTION_SLOP 0.2
# define PHYS_NUM_TYPES 7
/* Dynamic AABB Tree (DBVT) Broadphase */
# define DBVT_MAX_NODES 512
# define DBVT_MAX_LEAVES 256
# define DBVT_FAT_MARGIN 0.1
# define DBVT_NULL -1
/* Global Static Physics Params */
# define GRAVITY_CONSTANT -9.81
# define GRAVITY -9.81
# define GLOBAL_DAMPING 0.12
# define TIME_SCALE 1.0
# define MESH_SIMPLIFY 1
/* Compound body limits */
# define MAX_SUB_SHAPES 32
# define MAX_BODY_PAIRS 512
/* EPA */
# define EPA_MAX_ITER 30
# define EPA_MAX_FACES 64
# define EPA_MAX_VERTS 32
# define EPA_TOL 1e-5

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
}						t_phys_type;

/* Generic collider — kept for mesh capsule-simplification path */
typedef enum e_collider_type
{
	COLLIDER_SPHERE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
}						t_collider_type;

/* Forward declarations */
typedef t_vec3			(*t_support_fn)(const void *shape, t_vec3 dir);

/* One Lego brick: a convex sub-shape belonging to a compound body */
struct					s_sub_shape
{
	void				*shape;
	t_aabb				local_aabb;
	t_vec3				offset;
	t_mat4				transform;
	double				radius;
	t_phys_type			type;
};

/* Physics types - separation of concerns: per-object body and global state */
struct					s_physics_body
{
	t_vec3				velocity;
	t_vec3				angular_velocity;
	t_vec3				torque;
	double				mass;
	t_mat3				inv_inertia;
	double				elasticity;
	double				friction;
	bool				is_static;
	bool				is_compound;
	t_vec3				center;
	t_sub_shape			sub_shapes[MAX_SUB_SHAPES];
	size_t				sub_count;
	t_aabb				global_aabb;
	t_vec3				com;
};

/* Static BVH for Environment (Stage 12) */
struct					s_static_node
{
	t_aabb				aabb;
	int					left;
	int					right;
	int					obj_idx;
	int					obj_type;
};

struct					s_static_bvh
{
	t_static_node		*nodes;
	int					count;
	int					root;
};

/* One dynamic body in the DBVT (leaf) */
struct					s_dbvt_leaf
{
	t_aabb				fat_aabb;
	t_physics_body		*body;
	t_transform			*transform;
	void				*shape;
	t_support_fn		support;
	t_phys_type			type;
};

/* Internal tree node — holds merged AABB of subtree */
struct					s_dbvt_node
{
	t_aabb				aabb;
	int					left;
	int					right;
	int					leaf;
};

/* The full tree — static pool, rebuilt every frame */
struct					s_dbvt
{
	t_dbvt_node			nodes[DBVT_MAX_NODES];
	t_dbvt_leaf			leaves[DBVT_MAX_LEAVES];
	int					node_count;
	int					leaf_count;
	int					root;
};

/* ── THREAD POOL ── */

struct					s_gen_job
{
	struct s_scene		*scene;
	struct s_contact	*out;
	int					max_c;
	int					count;
	int					type;
	void				*arg;
};

struct					s_worker_arg
{
	struct s_scene		*scene;
	int					index;
};

struct					s_phys_pool
{
	pthread_t			threads[PHYS_NUM_TYPES];
	t_gen_job			jobs[PHYS_NUM_TYPES];
	sem_t				start[PHYS_NUM_TYPES];
	sem_t				done[PHYS_NUM_TYPES];
	t_worker_arg		args[PHYS_NUM_TYPES];
	int					shutdown;
	int					initialized;
};

/* ── PIPELINE TYPES ── */

struct					s_body_pair
{
	t_physics_body		*a;
	t_physics_body		*b;
	void				*la;
	void				*lb;
};

struct					s_shape_pair
{
	t_sub_shape			*sa;
	t_sub_shape			*sb;
	t_physics_body		*ba;
	t_physics_body		*bb;
};

struct					s_collider
{
	t_collider_type		type;
	union
	{
		double			radius;
		t_vec3			half_extents;
		t_vec3			normal;
		struct
		{
			t_vec3		a;
			t_vec3		b;
			double		radius;
		} capsule;
	} data;
};

/* Internal Contact Structure */
struct					s_contact
{
	t_physics_body		*a;
	t_transform			*ta;
	t_physics_body		*b;
	t_transform			*tb;
	t_vec3				normal;
	double				penetration;
	double				restitution;
	double				friction;
	t_vec3				contact_point;
	t_vec3				ra;
	t_vec3				rb;
};

/* ── SIMPLEX & EPA ── */

struct					s_simplex
{
	t_vec3				pts[4];
	t_vec3				a_pts[4];
	t_vec3				b_pts[4];
	int					n;
};

struct					s_epa_face
{
	int					idx[3];
	t_vec3				normal;
	double				dist;
};

struct					s_epa_poly
{
	t_vec3				pts[EPA_MAX_VERTS];
	t_vec3				a_pts[EPA_MAX_VERTS];
	t_vec3				b_pts[EPA_MAX_VERTS];
	int					n_verts;
	t_epa_face			faces[EPA_MAX_FACES];
	int					n_faces;
};

struct					s_edge
{
	int					a;
	int					b;
};

struct					s_epa_res
{
	t_vec3				normal;
	double				depth;
	t_vec3				contact_a;
	t_vec3				contact_b;
	void				*f;
};

struct					s_gjk_shape
{
	const void			*data;
	t_support_fn		support;
	t_vec3				center;
};

/* ── FUNCTION PROTOTYPES ── */

/* Update loops */
void					update_physics(struct s_scene *scene, double dt);
void					integrate_bodies(struct s_scene *scene, double dt);
int						generate_contacts(struct s_scene *scene,
							t_contact *contacts, int max_c);
void					phys_init_pool(struct s_scene *scene);
void					phys_destroy_pool(struct s_scene *scene);

/* AABB Calculations (Lego & Mesh) */
void					compute_mesh_aabb(struct s_mesh *mesh, t_aabb *out);
void					compute_primitive_aabb(t_sub_shape *s);
bool					aabb_overlap(t_aabb a, t_aabb b);
bool					aabb_overlap_broad(t_aabb a, t_aabb b);
bool					aabb_overlap_local(t_aabb a, t_aabb b);
void					phys_init_pool(struct s_scene *scene);
void					phys_destroy_pool(struct s_scene *scene);

/* Interaction */
void					physics_shoot_ray(struct s_scene *scene, t_ray ray,
							double impulse);
t_physics_body			*get_body_ref(struct s_scene *scene, t_bvh_ref ref);
int						query_sphere(struct s_scene *s, int idx,
							t_contact *c, int count, int max);
int						sphere_plane_contacts(struct s_scene *s, t_sphere *sp,
							t_gjk_shape *sa_gjk, t_contact *c, int count,
							int max);
int						sphere_others_contacts(struct s_scene *s, int idx,
							t_sphere *sp, t_aabb sa, t_gjk_shape *sa_gjk,
							t_contact *c, int count, int max);
int						traverse_bvh_contacts(struct s_scene *s, int idx,
							t_sphere *sp, t_aabb saabb, t_contact *c,
							int count, int max);
bool					detect_sphere_mesh_collision(const t_sphere *sp,
							struct s_mesh *m, t_vec3 *n, double *p);

/* Compound Body */
void					init_compound(t_physics_body *b, t_sub_shape *bricks,
							size_t n);
void					update_compound(t_physics_body *b);

/* Broadphase / Midphase */
int						broadphase(struct s_scene *s, t_body_pair *out,
							int max);
size_t					collect_bodies(struct s_scene *s,
							t_physics_body **out, size_t max);
int						query_static_bvh(struct s_scene *s, int node_idx,
							t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
							t_contact *c, int count, int max);
int						midphase(t_body_pair *pairs, int n, t_shape_pair *out,
							int max);

/* Solver */
void					solve_velocities(t_contact *contacts, int count);
void					solve_positions(t_contact *contacts, int count);
void					apply_torque(t_contact *c, t_physics_body *body,
							double impulse);

void					compute_ab_ao(t_simplex *s, t_vec3 *ab, t_vec3 *ao);
bool					handle_positive_simplex_line(t_vec3 ab, t_vec3 ao, t_vec3 *dir);
void					reduce_simplex_to_point(t_simplex *s, t_vec3 ao, t_vec3 *dir);

/* Support functions */
t_vec3					gjk_support_sphere(const void *data, t_vec3 dir);
t_vec3					gjk_support_box(const void *data, t_vec3 dir);
t_vec3					gjk_support_capsule(const void *data, t_vec3 dir);
t_vec3					gjk_support_cylinder(const void *data, t_vec3 dir);
t_vec3					gjk_support_rect(const void *data, t_vec3 dir);
t_vec3					gjk_support_tri(const void *data, t_vec3 dir);
t_vec3					gjk_support_pyramid(const void *data, t_vec3 dir);
t_vec3					gjk_support_mesh(const void *data, t_vec3 dir);

/* GJK / EPA */
bool					gjk_intersect(t_gjk_shape *a, t_gjk_shape *b,
							t_simplex *out);
bool					gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s,
							t_epa_res *res);
t_vec3					gjk_support_list(const t_vec3 *v, int count,
							t_vec3 dir);
t_vec3					bary(const t_vec3 tri[3], t_vec3 p);
t_epa_face				make_face(t_epa_poly *p, int i0, int i1, int i2);
int						closest_face(t_epa_poly *p);
void					collect_silhouette(t_epa_poly *p, t_vec3 support,
							t_edge *edges, int *n);
void					init_polytope(t_epa_poly *p, t_simplex *s);
void					get_contact_points(t_epa_poly *p, t_epa_face *f,
							t_vec3 *pa, t_vec3 *pb);
t_vec3					rot_by_ang(t_vec3 a, t_vec3 rot, double dt);
void					integrate_sphere(t_sphere *sp, double dt);
void					integrate_box(t_box *bx, double dt);
void					integrate_capsule(t_capsule *cap, double dt);
void					integrate_cylinder(t_cylinder *cy, double dt);
void					integrate_rect(t_rect *rc, double dt);
void					integrate_tri(t_tri_shape *tr, double dt);
void					integrate_pyramid(t_pyramid *py, double dt);
void					phys_dispatch_object(t_physics_body *b,
							t_transform *t, double dt);
void					phys_resolve_ccd(struct s_scene *s,
							t_physics_body *b, double dt);
void					phys_debug_spheres(struct s_scene *s);
t_static_bvh			*bvh_create(struct s_scene *s);
void					bvh_destroy(t_static_bvh *bvh);
void					apply_solver_torque(t_physics_body *b, t_vec3 r,
							t_vec3 imp, double inv_m, double s);
t_vec3					point_vel(t_physics_body *b, t_vec3 r);
double					ang_term(t_physics_body *b, t_vec3 r, t_vec3 n,
							double inv_m);
void					apply_friction(t_contact *ct, double inv_a,
							double inv_b, t_vec3 rv);
t_vec3					md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir,
							t_vec3 *pa, t_vec3 *pb);
int						pyramid_vs_plane(t_pyramid *py, t_plane *pl,
							t_contact *c, int max_c);
int						gjk_vs_plane(t_gjk_shape *sa, t_physics_body *ba,
							t_transform *ta, t_plane *pl, t_contact *c);
int						gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
							t_physics_body *ba, t_physics_body *bb,
							t_transform *ta, t_transform *tb, t_contact *c);
double					clamp_d(double v, double lo, double hi);
int						gjk_vs_all_planes(t_gjk_shape *sa, t_physics_body *ba,
							t_transform *ta, struct s_scene *s, t_contact *c,
							int count, int max);

/* Intersection Dispatch */
int						narrow_dispatch_body_pair(t_body_pair *p,
							t_contact *contacts, int count);
int						narrow_dispatch_shape_pair(t_shape_pair *p,
							t_contact *contacts, int count);

/* Primitive AABBs */
t_aabb					sphere_aabb(t_sphere *sp);
t_aabb					box_aabb(t_box *bx);
t_aabb					capsule_aabb(t_capsule *cp);
t_aabb					cylinder_aabb(t_cylinder *cy);
t_aabb					rect_aabb(t_rect *rc);
t_aabb					tri_aabb(t_tri_shape *tr);
t_aabb					pyramid_aabb(t_pyramid *py);

/* Tree-based Broadphase */
void					collect_leaves(struct s_scene *s, t_dbvt *t);
int						dbvt_build_range(t_dbvt *t, int first, int count);
void					build_dbvt(struct s_scene *s, t_dbvt *t);
int						dbvt_query_pairs(t_dbvt *t, t_body_pair *out,
							int max);

/* Primitive-Specific */
int						rect_vs_plane(t_rect *rc, t_plane *pl,
							t_contact *c, int max_c);
int						rect_vs_others(t_scene *s, int idx,
							t_rect *rc, t_aabb raabb, t_contact *c,
							int count, int max);
int						gjk_vs_rect(t_gjk_shape *sa, t_physics_body *ba,
							t_transform *ta, t_rect *rc, t_contact *c);
int						gjk_vs_tri(t_gjk_shape *sa, t_physics_body *ba,
							t_transform *ta, t_tri_shape *tr,
							t_contact *c);
int						gjk_vs_pyramid(t_gjk_shape *sa, t_physics_body *ba,
							t_transform *ta, t_pyramid *py,
							t_contact *c);
int						box_vs_plane(t_box *bx, t_plane *pl, t_contact *c,
							int max_c);
int						box_vs_others(t_scene *s, int idx, t_box *bx, t_aabb ba,
							t_contact *c, int count, int max);
int						capsule_plane_contacts(t_scene *s, t_capsule *cap,
							t_gjk_shape *sa, t_contact *c, int count, int max);
int						cap_vs_others(t_scene *s, int idx, t_capsule *cap,
							t_aabb ca, t_contact *c, int count, int max);
int						tri_vs_plane(t_tri_shape *tr, t_plane *pl, t_contact *c,
							int max_c);
int						tri_vs_others(t_scene *s, int idx, t_tri_shape *tr,
							t_aabb ta, t_contact *c, int count, int max);
int						cyl_plane_contacts(t_scene *s, t_cylinder *cy,
							t_gjk_shape *sa, t_contact *c, int count, int max);
int						cyl_vs_others(t_scene *s, int idx, t_cylinder *cy,
							t_aabb ca, t_contact *c, int count, int max);
bool					simplex_line(t_simplex *s, t_vec3 *dir);
bool					simplex_triangle(t_simplex *s, t_vec3 *dir);
bool					simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
void					update_simplex3(t_simplex *s, int a, int b, int c);

/* Gravity helper */
t_vec3					gravity_vec(void);

#endif
