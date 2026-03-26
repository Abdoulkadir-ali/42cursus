/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 14:35:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 15:46:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_TYPES_H
# define PHYSICS_TYPES_H

/* Opaque phys pool type: defined in physics implementation to avoid
	dragging threading headers and scene definitions into every user. */
/* Ensure we have thread primitives available for pool definitions */
# include <pthread.h>
# include <semaphore.h>

/* Minimal dependencies for data-only types */
# include "defines.h"
# include "maths.h"

/* Constants used by the types */
# ifndef MAX_SUB_SHAPES
#  define MAX_SUB_SHAPES 32
# endif
# ifndef EPA_MAX_VERTS
#  define EPA_MAX_VERTS 32
# endif
# ifndef EPA_MAX_FACES
#  define EPA_MAX_FACES 64
# endif
/* Broadphase / EPA runtime constants */
# ifndef MAX_BODY_PAIRS
#  define MAX_BODY_PAIRS 512
# endif
# ifndef EPA_MAX_ITER
#  define EPA_MAX_ITER 30
# endif
# ifndef EPA_TOL
#  define EPA_TOL 1e-5
# endif
/* Global damping applied during integration steps */
# ifndef GLOBAL_DAMPING
#  define GLOBAL_DAMPING 0.12
# endif
/* DBVT and EPA sizing constants */
# ifndef DBVT_MAX_NODES
#  define DBVT_MAX_NODES 512
# endif
# ifndef DBVT_MAX_LEAVES
#  define DBVT_MAX_LEAVES 256
# endif

/* Allow PHYS_NUM_TYPES to be overridden elsewhere */
# ifndef PHYS_NUM_TYPES
#  define PHYS_NUM_TYPES 7
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
	TYPE_PHYS_MESH
}						t_phys_type;

typedef enum e_collider_type
{
	COLLIDER_SPHERE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
}						t_collider_type;

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

/* Physics types - per-object body and global state (data only) */
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
	void				*owner;
	t_transform			*transform;
	t_sub_shape			sub_shapes[MAX_SUB_SHAPES];
	size_t				sub_count;
	t_aabb				global_aabb;
	t_vec3				com;
};

/* Generic collider description (data-only) */
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

/* Static BVH for Environment (small data-only node) */
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

/* DBVT (dynamic BVH) node/leaf structures (data-only) */
struct					s_dbvt_node
{
	t_aabb				aabb;
	int					left;
	int					right;
	int					leaf;
};

struct					s_dbvt_leaf
{
	t_aabb				fat_aabb;
	t_physics_body		*body;
	t_transform			*transform;
	void				*shape;
	t_support_fn		support;
	t_phys_type			type;
};

struct					s_dbvt
{
	t_dbvt_node			nodes[DBVT_MAX_NODES];
	t_dbvt_leaf			leaves[DBVT_MAX_LEAVES];
	int					node_count;
	int					leaf_count;
	int					root;
};

/* Internal Contact Structure (needed by job API) */
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

/* Thread pool job/worker types */
struct					s_gen_job
{
	t_scene				*scene;
	struct s_contact	*out;
	int               max_c;
	int               count;
	int               type;
	void              *arg;
};


struct					s_worker_arg
{
	t_scene				*scene;
	int               index;
};

struct					s_phys_pool
{
	pthread_t			threads[PHYS_NUM_TYPES];
	struct s_gen_job	jobs[PHYS_NUM_TYPES];
	sem_t				start[PHYS_NUM_TYPES];
	sem_t				done[PHYS_NUM_TYPES];
	struct s_worker_arg	args[PHYS_NUM_TYPES];
	int					shutdown;
	int					initialized;
};

/* Top-level physics engine object: binds a scene to the physics runtime */
struct s_physics
{
    struct s_scene    *scene;
    struct s_phys_pool *pool;
    double             damping;
    int                solver_iters;
};

typedef struct s_physics t_physics;
};

/* Pipeline helper types */
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

/* Simplex / EPA types */
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

#endif
