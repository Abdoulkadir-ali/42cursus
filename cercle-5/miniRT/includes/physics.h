/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:26:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:41:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

/* External dependencies */
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <semaphore.h>
# include <pthread.h>
# include <string.h>

# include "defines.h"
# include "maths.h"

/* Constants */
# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01
# define RESTITUTION_SLOP 0.2
# define PHYS_NUM_TYPES 7

/* Forward declarations */
struct s_scene;
struct s_sphere;
struct s_mesh;
struct s_physics_body;

/* ── BASE TYPES ── */

typedef t_vec3 (*t_support_fn)(const void *shape, t_vec3 dir);

/* Shape type discriminators for compound colliders */
typedef enum e_phys_type
{
	TYPE_PHYS_SPHERE,
	TYPE_PHYS_BOX,
	TYPE_PHYS_CAPSULE,
	TYPE_PHYS_CYLINDER,
	TYPE_PHYS_RECT,
	TYPE_PHYS_TRI,
	TYPE_PHYS_PYRAMID
}	t_phys_type;

/* Compound body limits */
# define MAX_SUB_SHAPES 32
# define MAX_BODY_PAIRS 512

/* One Lego brick: a convex sub-shape belonging to a compound body */
struct s_sub_shape {
	void		*shape;
	t_aabb		local_aabb;
	t_vec3		offset;
	t_mat4		transform;
	double		radius;
	t_phys_type	type;
};

/* Physics types - separation of concerns: per-object body and global state */
struct s_physics_body {
	t_vec3		velocity;
	t_vec3		angular_velocity;
	t_vec3		torque;
	double		mass;
	t_mat3		inv_inertia;
	double		elasticity;
	double		friction;
	bool		is_static;
	bool		is_compound;
	t_vec3		center;
	t_sub_shape	sub_shapes[MAX_SUB_SHAPES];
	size_t		sub_count;
	t_aabb		global_aabb;
	t_vec3		com;
};

/* ── ACCELERATION STRUCTURES ── */

/* Static BVH for Environment (Stage 12) */
struct s_static_node {
	t_aabb	aabb;
	int		left;
	int		right;
	int		obj_idx;
	int		obj_type;
};

struct s_static_bvh {
	t_static_node	*nodes;
	int				count;
	int				root;
};

/* Dynamic AABB Tree (DBVT) Broadphase */
# define DBVT_MAX_NODES 512
# define DBVT_MAX_LEAVES 256
# define DBVT_FAT_MARGIN 0.1
# define DBVT_NULL -1

/* One dynamic body in the DBVT (leaf) */
struct s_dbvt_leaf {
	t_aabb			fat_aabb;
	t_physics_body	*body;
	void			*shape;
	t_support_fn	support;
	t_phys_type		type;
};

/* Internal tree node — holds merged AABB of subtree */
struct s_dbvt_node {
	t_aabb	aabb;
	int		left;
	int		right;
	int		leaf;
};

/* The full tree — static pool, rebuilt every frame */
struct s_dbvt {
	t_dbvt_node	nodes[DBVT_MAX_NODES];
	t_dbvt_leaf	leaves[DBVT_MAX_LEAVES];
	int			node_count;
	int			leaf_count;
	int			root;
};

/* ── THREAD POOL ── */

struct s_gen_job {
	struct s_scene		*scene;
	struct s_contact	*out;
	int					max_c;
	int					count;
	int					type;
	void				*arg;
};

struct s_worker_arg {
	struct s_scene	*scene;
	int				index;
};

struct s_phys_pool {
	pthread_t		threads[PHYS_NUM_TYPES];
	t_gen_job		jobs[PHYS_NUM_TYPES];
	sem_t			start[PHYS_NUM_TYPES];
	sem_t			done[PHYS_NUM_TYPES];
	t_worker_arg	args[PHYS_NUM_TYPES];
	int				shutdown;
	int				initialized;
};

/* ── PIPELINE TYPES ── */

struct s_body_pair {
	t_physics_body			*a;
	t_physics_body			*b;
	void					*la;
	void					*lb;
};

struct s_shape_pair {
	t_sub_shape			*sa;
	t_sub_shape			*sb;
	t_physics_body			*ba;
	t_physics_body			*bb;
};

/* Global Static Physics Params */
# define GRAVITY_VEC ((t_vec3){0, -9.81, 0, 0})
# define GLOBAL_DAMPING 0.12
# define TIME_SCALE 1.0
# define MESH_SIMPLIFY 1

/* Generic collider — kept for mesh capsule-simplification path */
typedef enum e_collider_type
{
	COLLIDER_SPHERE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
}               t_collider_type;

struct s_collider {
	t_collider_type    type;
	union {
		double      radius;
		t_vec3      half_extents;
		t_vec3      normal;
		struct {
			t_vec3 a;
			t_vec3 b;
			double radius;
		};
	} data;
}               t_collider;

/* Internal Contact Structure */
struct s_contact {
    t_physics_body  *a;
    t_transform     *ta;
    t_physics_body  *b;
    t_transform     *tb;
    t_vec3          normal;
    double          penetration;
    double          restitution;
    double          friction;
    t_vec3          contact_point;
    t_vec3          ra;
    t_vec3          rb;
};

/* ── SIMPLEX & EPA ── */

struct s_simplex {
	t_vec3	pts[4];
	t_vec3	a_pts[4];
	t_vec3	b_pts[4];
	int		n;
};

# define EPA_MAX_ITER 30
# define EPA_MAX_FACES 64
# define EPA_MAX_VERTS 32
# define EPA_TOL 1e-5

struct s_epa_face {
	int		idx[3];
	t_vec3	normal;
	double	dist;
};

struct s_epa_poly {
	t_vec3		pts[EPA_MAX_VERTS];
	t_vec3		a_pts[EPA_MAX_VERTS];
	t_vec3		b_pts[EPA_MAX_VERTS];
	int			n_verts;
	t_epa_face	faces[EPA_MAX_FACES];
	int			n_faces;
};

struct s_edge {
	int	a;
	int	b;
};

struct s_epa_res {
	t_vec3		normal;
	double		depth;
	t_vec3		contact_a;
	t_vec3		contact_b;
	void		*f;
};

struct s_gjk_shape {
	const void		*data;
	t_support_fn	support;
	t_vec3			center;
};

/* ── FUNCTION PROTOTYPES ── */

/* Update loops */
void	update_physics(struct s_scene *scene, double dt);
void	integrate_bodies(struct s_scene *scene, double dt);
int     generate_contacts(struct s_scene *scene, t_contact *contacts, int max_c);
void	phys_init_pool(struct s_scene *scene);
void	phys_destroy_pool(struct s_scene *scene);

/* AABB Calculations (Lego & Mesh) */
void	compute_mesh_aabb(struct s_mesh *mesh, t_aabb *out);
void	compute_primitive_aabb(t_sub_shape *s);
void	phys_init_pool(struct s_scene *scene);
void	phys_destroy_pool(struct s_scene *scene);

/* Interaction */
void	physics_shoot_ray(struct s_scene *scene, t_ray ray, double impulse);
t_physics_body	*get_body_ref(struct s_scene *scene, t_bvh_ref ref);

/* Compound Body */
void	init_compound(t_physics_body *b, t_sub_shape *bricks, size_t n);
void	update_compound(t_physics_body *b);

/* Broadphase / Midphase */
int	broadphase(struct s_scene *s, t_body_pair *out, int max);
int	midphase(t_body_pair *pairs, int n, t_shape_pair *out, int max);

/* Solver */
void	solve_velocities(t_contact *contacts, int count);
void	solve_positions(t_contact *contacts, int count);
void	apply_torque(t_contact *c, t_physics_body *body, double impulse);

/* Support functions */
t_vec3	gjk_support_sphere(const void *data, t_vec3 dir);
t_vec3	gjk_support_box(const void *data, t_vec3 dir);
t_vec3	gjk_support_capsule(const void *data, t_vec3 dir);
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir);
t_vec3	gjk_support_rect(const void *data, t_vec3 dir);
t_vec3	gjk_support_tri(const void *data, t_vec3 dir);
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir);
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir);

/* GJK / EPA */
bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out);
bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s, t_epa_res *res);
int		gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
			t_physics_body *ba, t_physics_body *bb,
			t_transform *ta, t_transform *tb,
			t_contact *c);

/* Utils */
double  clamp_d(double v, double lo, double hi);

#endif
