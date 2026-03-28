/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:26:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 11:06:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

/* EXTERNAL DEPENDENCIES */
# include <pthread.h>
# include <semaphore.h>

/* NEUTRAL DEPENCIES */
# include "objects.h"
# include "scene.h"
# include "surface.h"
# include "dod.h"

/* ----------------------------- physics types ----------------------------- */
# ifndef MAX_SUB_SHAPES
# endif
# ifndef EPA_MAX_VERTS
# endif
# ifndef EPA_MAX_FACES
# endif
# ifndef MAX_BODY_PAIRS
# endif
# ifndef EPA_MAX_ITER
# endif
# ifndef EPA_TOL
# endif
# ifndef GLOBAL_DAMPING
# endif
# ifndef DBVT_MAX_NODES
# endif
# ifndef DBVT_MAX_LEAVES
# endif

// Lightweight per-body physics config used by the editor UI and snapshots.
// Actual simulation data lives in t_physics_soa.
typedef struct s_physics_body
{
	float					mass;
	float					elasticity;
	float					friction;
	bool					is_static;
}							t_physics_body;

typedef enum e_phys_type
{
	TYPE_PHYS_SPHERE,
	TYPE_PHYS_BOX,
	TYPE_PHYS_CAPSULE,
	TYPE_PHYS_CYLINDER,
	TYPE_PHYS_RECT,
	TYPE_PHYS_TRI,
	TYPE_PHYS_PYRAMID,
	TYPE_PHYS_MESH,
	TYPE_PHYS_MAX
}							t_phys_type;

typedef struct s_compound_part_soa
{
	int *parent_idx; /* index into t_physics_soa */
	t_phys_type				*type;
	float					*offset_x;
	float					*offset_y;
	float					*offset_z;
	float					*radius;
	float					*height;
	float					*half_extents[3];
	size_t					count;
	size_t					cap;
}							t_compound_part_soa;

typedef struct s_phys_hot
{
	float					*vx;
	float					*vy;
	float					*vz;
	float					*ang_vx;
	float					*ang_vy;
	float					*ang_vz;
	float					*amin_x;
	float					*amin_y;
	float					*amin_z;
	float					*amax_x;
	float					*amax_y;
	float					*amax_z;
}							t_phys_hot;

typedef struct s_physics_soa
{
	t_phys_hot				hot;
	int						*prim_idx;
	float					*mass;
	float					*inv_mass;
	float					*elasticity;
	float					*friction;
	float					*inv_ix;
	float					*inv_iy;
	float					*inv_iz;
	uint8_t					*is_static;
	uint8_t					*is_compound;
	int						*first_part;
	int						*part_count;
	size_t					count;
	size_t					cap;
}							t_physics_soa;

typedef struct s_static_node
{
	t_aabb					aabb;
	int						left;
	int						right;
	int						prim_idx;
}							t_static_node;

typedef struct s_static_bvh
{
	t_static_node			*nodes;
	int						count;
	int						root;
}							t_static_bvh;

typedef struct s_dbvt_node
{
	t_aabb					aabb;
	int						left;
	int						right;
	int						leaf;
}							t_dbvt_node;

typedef struct s_dbvt_leaf
{
	t_aabb					fat_aabb;
	int						prim_idx;
	t_phys_type				type;
}							t_dbvt_leaf;

typedef struct s_dbvt
{
	t_dbvt_node				nodes[DBVT_MAX_NODES];
	t_dbvt_leaf				leaves[DBVT_MAX_LEAVES];
	int						node_count;
	int						leaf_count;
	int						root;
}							t_dbvt;

typedef struct s_contact
{
	int						idx_a;
	int						idx_b;
	t_vec3					normal;
	double					penetration;
	double					restitution;
	double					friction;
	t_vec3					contact_point;
	t_vec3					ra;
	t_vec3					rb;
}							t_contact;

typedef struct s_gen_job
{
	t_scene					*scene;
	struct s_contact		*out;
	int						max_c;
	int						count;
	int						type;
	void					*arg;
}							t_gen_job;

typedef struct s_worker_arg
{
	t_scene					*scene;
	int						index;
}							t_worker_arg;

typedef struct s_phys_pool
{
	pthread_t				threads[PHYS_NUM_TYPES];
	struct s_gen_job		jobs[PHYS_NUM_TYPES];
	sem_t					start[PHYS_NUM_TYPES];
	sem_t					done[PHYS_NUM_TYPES];
	struct s_worker_arg		args[PHYS_NUM_TYPES];
	int						shutdown;
	int						initialized;
}							t_phys_pool;

typedef struct s_physics
{
	struct s_scene			*scene;
	t_physics_soa			*soa;
	t_compound_part_soa		*comp;
	struct s_phys_pool		*pool;
	t_dbvt					dbvt;
	t_static_bvh			*static_bvh;
	t_vec3					gravity;
	double					damping;
	double					fixed_dt;
	int						solver_iters;
	bool					needs_bake;
	uint32_t				baked_version;
}							t_physics;

typedef struct s_body_pair
{
	int						idx_a;
	int						idx_b;
}							t_body_pair;

typedef struct s_simplex
{
	t_vec3					pts[4];
	t_vec3					a_pts[4];
	t_vec3					b_pts[4];
	int						n;
}							t_simplex;

typedef struct s_epa_face
{
	int						idx[3];
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

typedef struct s_edge
{
	int						a;
	int						b;
}							t_edge;

typedef struct s_epa_res
{
	t_vec3					normal;
	double					depth;
	t_vec3					contact_a;
	t_vec3					contact_b;
	void					*f;
}							t_epa_res;

typedef struct s_gjk_shape	t_gjk_shape;

struct						s_gjk_shape
{
	struct s_scene			*scene;
	int						idx;
};

typedef t_vec3				(*t_support_fn)(const struct s_gjk_shape *s,
					t_vec3 dir);
/* --------------------------- end physics types --------------------------- */

/* ── FUNCTION PROTOTYPES ── */

/* GUI-facing physics settings (small, safe to include) */
typedef struct s_physics_settings
{
	bool					simulate_physics;
	t_vec3					gravity;
	double					damping;
	double					fixed_dt;
	int						solver_iters;
}							t_physics_settings;

/* Minimal facade for GUI: simulate the scene without importing internals */
void						simulate_physics(struct s_scene *scene, double dt);
void						update_physics_settings(t_physics *phys,
								const t_physics_settings *s);
void						get_physics_settings(const t_physics *phys,
								t_physics_settings *out);
/* Physics SoA Management */
void						init_physics_soa(t_physics_soa *p);
void						destroy_physics_soa(t_physics_soa *p);
bool						realloc_physics_soa(t_physics_soa *p,
								size_t new_cap);
bool						soa_add_body(t_physics_soa *p,
								t_primitive_array *prims, int prim_idx);
void						update_physics(struct s_scene *scene, double dt);
void						integrate_bodies(struct s_scene *scene, double dt);
int							generate_contacts(struct s_scene *scene,
								t_contact *contacts, int max_c);
void						phys_init_pool(struct s_scene *scene);
void						phys_destroy_pool(struct s_scene *scene);

/* New physics engine interface (preferred): create, destroy and simulate */
t_physics					*phys_create(struct s_scene *scene);
void						phys_destroy(t_physics *phys);
void						phys_simulate(t_physics *phys, double dt);

/* Intersection Dispatch */
void						physics_shoot_ray(struct s_scene *scene, t_ray ray,
								double impulse);
int							query_prim(struct s_scene *s, int idx, t_contact *c,
								int count, int max);
int							prim_plane_contacts(struct s_scene *s, int idx,
								t_gjk_shape *sa_gjk, t_contact *c, int count,
								int max);
int							prim_others_contacts(struct s_scene *s, int idx,
								t_aabb sa, t_gjk_shape *sa_gjk, t_contact *c,
								int count, int max);
int							traverse_bvh_contacts(struct s_scene *s, int idx,
								t_aabb saabb, t_contact *c, int count, int max);
bool						detect_prim_mesh_collision(struct s_scene *s,
								int idx, struct s_mesh *m, t_vec3 *n,
								double *p);

/* Compound Body */
void						update_compound(t_physics *phys, int body_idx);
void						compute_com(t_physics *phys, int body_idx);
void						compute_inertia(t_physics *phys, int body_idx);

/* Broadphase / Midphase */
int							broadphase(struct s_scene *s, t_body_pair *out,
								int max);
int							query_static_bvh(struct s_scene *s, int node_idx,
								t_gjk_shape *sa, int body_idx, t_contact *c,
								int count, int max);

/* Solver */
void						solve_velocities(t_contact *contacts, int count);
void						solve_positions(t_contact *contacts, int count);
void						apply_torque(struct s_scene *s, t_contact *c,
								int body_idx, double impulse);

void						compute_ab_ao(t_simplex *s, t_vec3 *ab, t_vec3 *ao);
bool						handle_positive_simplex_line(t_vec3 ab, t_vec3 ao,
								t_vec3 *dir);
void						reduce_simplex_to_point(t_simplex *s, t_vec3 ao,
								t_vec3 *dir);

/* Support functions */
t_vec3						gjk_support_sphere(const t_gjk_shape *s,
								t_vec3 dir);
t_vec3						gjk_support_box(const t_gjk_shape *s, t_vec3 dir);
t_vec3						gjk_support_capsule(const t_gjk_shape *s,
								t_vec3 dir);
t_vec3						gjk_support_cylinder(const t_gjk_shape *s,
								t_vec3 dir);
t_vec3						gjk_support_rect(const t_gjk_shape *s, t_vec3 dir);
t_vec3						gjk_support_tri(const t_gjk_shape *s, t_vec3 dir);
t_vec3						gjk_support_pyramid(const t_gjk_shape *s,
								t_vec3 dir);
t_vec3						gjk_support_mesh(const t_gjk_shape *s, t_vec3 dir);
t_vec3						gjk_support_compound(const t_gjk_shape *s,
								t_vec3 dir);

/* GJK / EPA */
bool						gjk_intersect(t_gjk_shape *a, t_gjk_shape *b,
								t_simplex *out);
bool						gjk_epa(t_gjk_shape *a, t_gjk_shape *b,
								t_simplex *s, t_epa_res *res);
t_vec3						gjk_support_list(const t_vec3 *v, int count,
								t_vec3 dir);
t_vec3						bary(const t_vec3 tri[3], t_vec3 p);
t_epa_face					make_face(t_epa_poly *p, int i0, int i1, int i2);
int							closest_face(t_epa_poly *p);
void						collect_silhouette(t_epa_poly *p, t_vec3 support,
								t_edge *edges, int *n);
void						init_polytope(t_epa_poly *p, t_simplex *s);
void						get_contact_points(t_epa_poly *p, t_epa_face *f,
								t_vec3 *pa, t_vec3 *pb);
t_vec3						rot_by_ang(t_vec3 a, t_vec3 rot, double dt);
void						integrate_prim(struct s_scene *scene, int idx,
								double dt);
void						phys_dispatch_object(struct s_scene *s,
								int body_idx, double dt);
void						phys_resolve_ccd(struct s_scene *s, int body_idx,
								double dt);
void						phys_debug_spheres(struct s_scene *s);
/* Raytracing BVH functions are declared in raytracing.h; keep physics
** headers free of conflicting bvh_* declarations. */
void						apply_solver_torque(t_physics *p, int body_idx,
								t_vec3 r, t_vec3 imp, double inv_m, double s);
t_vec3						point_vel(t_physics *p, int body_idx, t_vec3 r);
double						ang_term(t_physics *p, int body_idx, t_vec3 r,
								t_vec3 n, double inv_m);
void						apply_friction(t_contact *ct, double inv_a,
								double inv_b, t_vec3 rv);
t_vec3						md_support(t_gjk_shape *a, t_gjk_shape *b,
								t_vec3 dir, t_vec3 *pa, t_vec3 *pb);
int							prim_vs_plane(struct s_scene *s, int prim_idx,
								int plane_idx, t_contact *c, int max_c);
int							gjk_vs_plane(struct s_scene *s, t_gjk_shape *sa,
								int body_idx, int plane_idx, t_contact *c);
int							gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
								int idx_a, int idx_b, t_contact *c);
double						clamp_d(double v, double lo, double hi);
int							gjk_vs_all_planes(t_gjk_shape *sa, int body_idx,
								struct s_scene *s, t_contact *c, int count,
								int max);

/* Tree-based Broadphase */
void						collect_leaves(struct s_scene *s, t_dbvt *t);
int							dbvt_build_range(t_dbvt *t, int first, int count);
void						build_dbvt(struct s_scene *s, t_dbvt *t);
int							dbvt_query_pairs(t_dbvt *t, t_body_pair *out,
								int max);

/* Primitive-Specific */
int							gjk_vs_others(struct s_scene *s, int idx,
								t_aabb saabb, t_contact *c, int count, int max);
bool						simplex_line(t_simplex *s, t_vec3 *dir);
bool						simplex_triangle(t_simplex *s, t_vec3 *dir);
bool						simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
void						update_simplex3(t_simplex *s, int a, int b, int c);

/* Gravity helper */
t_vec3						gravity_vec(void);

#endif
