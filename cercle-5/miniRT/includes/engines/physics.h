/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:26:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 13:45:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H
/* --- CONSTANTS --- */
# define GRAVITY -9.81
# define BAUMGARTE 0.2
# define SLOP 0.01
# define RESTITUTION_SLOP 0.2
# define GLOBAL_DAMPING 0.12
# define SOLVER_ITERATIONS 8
# define MAX_BODY_PAIRS 512
# define MAX_CONTACTS 1024
# define PHYS_NUM_TYPES 7

/* GJK/EPA */
# define EPA_MAX_FACES 64
# define EPA_MAX_ITER 30
# define EPA_MAX_VERTS 32
# define EPA_TOL 1e-5

/* Dynamic BVH */
# define DBVT_FAT_MARGIN 0.1
# define DBVT_MAX_LEAVES 256
# define DBVT_MAX_NODES 512
# define DBVT_NULL -1

/* EXTERNAL DEPENDENCIES */
# include <pthread.h>
# include <semaphore.h>

/* NEUTRAL DEPENCIES */
# include "parser.h"
# include "scene.h"
# include "surface.h"
# include "unpacker.h"

/* ----------------------------- physics types ----------------------------- */
# ifndef MAX_SUB_SHAPES /* Defined authoritatively in objects.h */
#  define MAX_SUB_SHAPES 32
# endif

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

typedef struct s_sub_shape
{
	t_phys_type				type;
	t_vec3					offset;
	t_aabb					local_aabb;
	void					*data;
}							t_sub_shape;

typedef struct s_shape_pair
{
	int						body_a;
	int						body_b;
	t_sub_shape				*shape_a;
	t_sub_shape				*shape_b;
}							t_shape_pair;

// Lightweight per-body physics config used by the editor UI and snapshots.
// Actual simulation data lives in t_physics_soa.
typedef struct s_physics_body
{
	double					mass;
	double					elasticity;
	double					friction;
	bool					is_static;
	bool					is_compound;
	size_t					sub_count;
	t_sub_shape				sub_shapes[MAX_SUB_SHAPES];
	t_vec3					com;
	t_mat3					inv_inertia;
	t_aabb					global_aabb;
}							t_physics_body;

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
	t_scene					*scene;
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

typedef t_vec3				(*t_support_fn)(const struct s_gjk_shape *s,
					t_vec3 dir);

struct						s_gjk_shape
{
	struct s_scene			*scene;
	struct s_physics		*phys;
	int						idx;
	t_support_fn			support;
};
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
void						simulate_physics(t_physics *phys, double dt);
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
void						update_physics(t_physics *phys, double dt);
void						integrate_bodies(t_physics *phys, double dt);
int							generate_contacts(t_physics *phys,
								t_contact *contacts, int max_c);
void						phys_init_pool(t_physics *phys);
void						phys_destroy_pool(t_physics *phys);

/* New physics engine interface (preferred): create, destroy and simulate */
t_physics					*phys_create(struct s_scene *scene);
void						phys_destroy(t_physics *phys);
void						phys_simulate(t_physics *phys, double dt);
void						phys_bake_scene(t_physics *phys,
							struct s_scene *scene);
double						solve_one_velocity(t_physics *p, t_contact *ct,
							double inv_a, double inv_b);
void						apply_position_correction(t_physics *phys,
							t_contact *ct, double inv_a, double inv_b);

/* Intersection Dispatch */
void						physics_apply_impulse(t_physics *phys, int prim_idx,
								t_vec3 impulse);
int							query_prim(t_physics *phys, int idx, t_contact *c,
								int count, int max);
int							query_sphere(t_physics *phys, int idx, t_contact *c,
								int count, int max);
int							query_box(t_physics *phys, int idx, t_contact *c,
								int count, int max);
int							query_rect(t_physics *phys, int idx, t_contact *c,
								int count, int max);
int							query_capsule(t_physics *phys, int idx,
								t_contact *c, int count, int max);
int							query_cylinder(t_physics *phys, int idx,
								t_contact *c, int count, int max);
int							query_pyramid(t_physics *phys, int idx,
								t_contact *c, int count, int max);
int							query_tri(t_physics *phys, int idx, t_contact *c,
								int count, int max);

int							prim_plane_contacts(t_physics *phys, int idx,
								t_contact *c, int count,
								int max);
int							prim_others_contacts(t_physics *phys, int idx,
								t_aabb sa, t_gjk_shape *sa_gjk, t_contact *c,
								int count, int max);
int							traverse_bvh_contacts(t_physics *phys, int idx,
								t_aabb saabb, t_contact *c, int count, int max);
bool						detect_prim_mesh_collision(t_physics *phys, int idx,
								struct s_mesh *m, t_vec3 *n, double *p);

/* Compound Body */
void						init_compound(t_physics_body *b,
								t_sub_shape *bricks, size_t n);
void						update_compound(t_physics_body *b);
void						compute_com(t_physics_body *b);
void						compute_inertia(t_physics_body *b);

/* Broadphase / Midphase */
int							query_static_bvh(t_physics *phys, int node_idx,
								t_gjk_shape *sa, int body_idx, t_contact *c,
								int count, int max);

/* Solver */
void						solve_velocities(t_physics *phys,
								t_contact *contacts, int count);
void						solve_positions(t_physics *phys,
								t_contact *contacts, int count);
void						apply_torque(t_physics *phys, t_contact *c,
								int body_idx, double impulse);

void						compute_ab_ao(t_simplex *s, t_vec3 *ab, t_vec3 *ao);
bool						handle_positive_simplex_line(t_vec3 ab, t_vec3 ao,
								t_vec3 *dir);
void						reduce_simplex_to_point(t_simplex *s, t_vec3 ao,
								t_vec3 *dir);
t_support_fn				get_support(int type);
void						init_gjk_shape(t_gjk_shape *s, t_physics *phys,
								int idx);

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
int							collision_closest_face(t_epa_poly *p);
void							collect_silhouette(t_epa_poly *p, t_vec3 support,
								t_edge *edges, int *n);
void							init_polytope(t_epa_poly *p, t_simplex *s);
void							get_contact_points(t_epa_poly *p, t_epa_face *f, t_vec3 *pa, t_vec3 *pb);
void							collision_init_polytope(t_epa_poly *p, t_simplex *s);
void							collision_get_contact_points(t_epa_poly *p, t_epa_face *f, t_vec3 *pa, t_vec3 *pb);
void							push_face(t_epa_poly *p, int i0, int i1, int i2);
void							expand(t_epa_poly *p, t_vec3 pt, t_vec3 pa, t_vec3 pb);
t_vec3						rot_by_ang(t_vec3 a, t_vec3 rot, double dt);
void						integrate_prim(t_physics *phys, int idx, double dt);
void						phys_dispatch_object(t_physics *phys, int body_idx,
								double dt);
void						phys_resolve_ccd(t_physics *phys, int body_idx,
								double dt);
void						phys_debug_spheres(t_physics *phys);
/* Raytracing BVH functions are declared in raytracing.h; keep physics
** headers free of conflicting bvh_* declarations. */
void						apply_solver_torque(t_physics *p, int body_idx,
								t_vec3 r, t_vec3 imp, double inv_m, double s);
t_vec3						point_vel(t_physics *p, int body_idx, t_vec3 r);
double						ang_term(t_physics *p, int body_idx, t_vec3 r,
								t_vec3 n, double inv_m);
void						apply_friction(t_physics *phys, t_contact *ct,
							double inv_a, double inv_b, t_vec3 rv);
t_vec3						md_support(t_gjk_shape *a, t_gjk_shape *b,
								t_vec3 dir, t_vec3 *pa, t_vec3 *pb);
int							prim_vs_plane(t_physics *phys, int prim_idx,
								int plane_idx, t_contact *c, int max_c);
int							gjk_make_contact(t_physics *phys, int idx_a,
								int idx_b, t_contact *c);
int							gjk_vs_plane(t_physics *phys, int body_idx,
								int plane_idx, t_contact *c);
int							gjk_vs_all_planes(t_gjk_shape *sa, int body_idx,
								t_physics *phys, t_contact *c, int count,
								int max);

/* Tree-based Broadphase */
void						collect_leaves(t_physics *phys, t_dbvt *t);
int							dbvt_build_range(t_dbvt *t, int first, int count);
void						build_dbvt(t_physics *phys, t_dbvt *t);
int							dbvt_query_pairs(t_dbvt *t, t_body_pair *out,
								int max);

/* Primitive-Specific */
int							gjk_vs_others(t_physics *phys, int idx,
								t_aabb saabb, t_contact *c, int count, int max);
bool						simplex_line(t_simplex *s, t_vec3 *dir);
bool						simplex_triangle(t_simplex *s, t_vec3 *dir);
bool						simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
void						update_simplex3(t_simplex *s, int a, int b, int c);

/* Gravity helper */
t_vec3						gravity_vec(void);

#endif
