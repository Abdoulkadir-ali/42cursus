/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:26:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:26:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHYSICS_H
# define PHYSICS_H

# include "core.h"
# include "maths.h"
# include "scene.h"
# include <semaphore.h>
# include <pthread.h>
# include <string.h>

static t_phys_pool	g_pool;

/* Constants */
# define MAX_CONTACTS 1024
# define SOLVER_ITERATIONS 8
# define BAUMGARTE 0.2
# define SLOP 0.01
# define RESTITUTION_SLOP 0.2
# define PHYS_NUM_TYPES 7

/* Forward declarations */
struct s_scene;

typedef struct s_gen_job
{
	struct s_scene		*scene;
	struct s_contact	*out;
	int					max_c;
	int					count;
	int					type;
}	t_gen_job;


typedef struct s_phys_pool
{
	pthread_t	threads[PHYS_NUM_TYPES];
	t_gen_job	jobs[PHYS_NUM_TYPES];
	int			indices[PHYS_NUM_TYPES];
	sem_t		start[PHYS_NUM_TYPES];
	sem_t		done[PHYS_NUM_TYPES];
	int			shutdown;
	int			initialized;
}	t_phys_pool;


/* Global Static Physics Params */
# define GRAVITY_VEC ((t_vec3){0, -9.81, 0, 0})
# define GLOBAL_DAMPING 0.12
# define TIME_SCALE 1.0
# define MESH_SIMPLIFY 1

/* Compound body limits */
# define MAX_SUB_SHAPES 32
# define MAX_BODY_PAIRS 512

/* Dynamic AABB Tree (DBVT) Broadphase */
# define DBVT_MAX_NODES 512
# define DBVT_MAX_LEAVES 256
# define DBVT_FAT_MARGIN 0.1
# define DBVT_NULL -1

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

/* One Lego brick: a convex sub-shape belonging to a compound body */
typedef struct s_sub_shape
{
	void		*shape;      /* ptr to t_sphere, t_box, etc. */
	t_aabb		local_aabb;  /* AABB in body space (pre-computed) */
	t_vec3		offset;      /* position relative to body CoM */
	t_phys_type	type;
}	t_sub_shape;

/* 3-tier pipeline intermediate results */
typedef struct s_body_pair
{
	struct s_physics_body	*a;
	struct s_physics_body	*b;
}	t_body_pair;

typedef struct s_shape_pair
{
	t_sub_shape			*sa;
	t_sub_shape			*sb;
	struct s_physics_body	*ba;
	struct s_physics_body	*bb;
}	t_shape_pair;

/* One dynamic body in the DBVT (leaf) */
typedef struct s_dbvt_leaf
{
	t_aabb			fat_aabb;   /* AABB expanded by DBVT_FAT_MARGIN */
	t_physics_body	*body;
	void			*shape;     /* ptr to original t_sphere / t_box / etc. */
	t_support_fn	support;    /* GJK support function for this shape */
	t_phys_type		type;
}	t_dbvt_leaf;

/* Internal tree node — holds merged AABB of subtree */
typedef struct s_dbvt_node
{
	t_aabb	aabb;
	int		left;   /* index into nodes[], DBVT_NULL = none */
	int		right;
	int		leaf;   /* index into leaves[], DBVT_NULL = internal node */
}	t_dbvt_node;

/* The full tree — static pool, rebuilt every frame */
typedef struct s_dbvt
{
	t_dbvt_node	nodes[DBVT_MAX_NODES];
	t_dbvt_leaf	leaves[DBVT_MAX_LEAVES];
	int			node_count;
	int			leaf_count;
	int			root;       /* index of root node */
}	t_dbvt;


/* Forward declarations to avoid circular includes. Concrete types
 * are included in implementation files when needed. */

/* Physics types - separation of concerns: per-object body and global state */
typedef struct s_physics_body
{
	/* Motion state */
	t_vec3		velocity;
	t_vec3		angular_velocity;
	t_vec3		torque;
	/* Inertia */
	double		mass;
	t_vec3		inv_inertia;
	/* Material */
	double		elasticity;
	double		friction;
	/* Flags */
	bool		is_static;
	bool		is_compound;
	/* Single-body CoM (legacy path) */
	t_vec3		center;
	/* Compound Backpack */
	t_sub_shape	sub_shapes[MAX_SUB_SHAPES];
	size_t		sub_count;
	t_aabb		global_aabb;
	t_vec3		com;
}				t_physics_body;

/* Physics update loop */
void	update_physics(t_scene *scene, double dt);

/* Physics debug */
void	phys_debug_spheres(t_scene *scene);

/* Sphere-mesh collision (mesh/collision.c) */

bool    detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
				t_vec3 *out_normal, double *out_penetration);

/* Generic collider — kept for mesh capsule-simplification path */
typedef enum e_collider_type
{
	COLLIDER_SPHERE,
	COLLIDER_BOX,
	COLLIDER_PLANE,
	COLLIDER_CAPSULE
}               t_collider_type;

typedef struct s_collider
{
	t_collider_type    type;
	union {
		double      radius;
		t_vec3      half_extents;
		t_vec3      normal;
		struct {
			t_vec3 a;
			t_vec3 b;
			double radius;
		} capsule;
	} data;
}               t_collider;

/* Interaction */
void	physics_shoot_ray(t_scene *scene, t_ray ray, double impulse);



/* Internal Contact Structure */
typedef struct s_contact
{
    t_physics_body  *a;
    t_transform     *ta;
    t_physics_body  *b;
    t_transform     *tb;
    t_vec3          normal;     /* From A to B */
    double          penetration;
    double          restitution;
    double          friction;
    t_vec3          contact_point; /* World space */
    t_vec3          ra; /* Vector from Center A to Contact Point */
    t_vec3          rb; /* Vector from Center B to Contact Point */
}               t_contact;

/* Integration */
void    integrate_bodies(t_scene *scene, double dt);


/* Collision Detection */
int     generate_contacts(t_scene *scene, t_contact *contacts, int max_c);

/* ── GJK / EPA ──────────────────────────────────────────────────────────── */

/*
** Unified convex shape interface for GJK.
** 'support' returns the world-space point furthest along dir.
** 'center'  is the world-space center of mass.
*/
typedef t_vec3 (*t_support_fn)(const void *shape, t_vec3 dir);

typedef struct s_gjk_shape
{
	const void		*data;
	t_support_fn	support;
	t_vec3			center;
}	t_gjk_shape;

/* Interaction Utils */
t_vec3			rot_by_ang(t_vec3 v, t_vec3 w, double dt);
t_physics_body	*get_body_ref(t_scene *scene, t_hit_ref ref);

/* Compound Body */
void	init_compound(t_physics_body *b, t_sub_shape *bricks, size_t n);
void	update_compound(t_physics_body *b);

/* Broadphase / Midphase */
int	broadphase(t_scene *s, t_body_pair *out, int max);
int	midphase(t_body_pair *pairs, int n, t_shape_pair *out, int max);

/* Solver Torque */
void	apply_torque(t_contact *c, t_physics_body *body, double impulse);

/* Collision Queries */
int	query_sphere(t_scene *s, int idx, t_contact *c, int count, int max);
int	traverse_bvh_contacts(t_scene *s, int idx, t_sphere *sp, t_aabb saabb,
		t_contact *c, int count, int max);
int	sphere_plane_contacts(t_scene *s, t_sphere *sp, t_gjk_shape *sa,
		t_contact *c, int count, int max);
int	sphere_others_contacts(t_scene *s, int idx, t_sphere *sp, t_aabb sa,
		t_gjk_shape *sa_gjk, t_contact *c, int count, int max);

int	query_rect(t_scene *s, int idx, t_contact *c, int count, int max);
int	rect_vs_plane(t_rect *rc, t_plane *pl, t_contact *c, int max_c);
int	rect_vs_others(t_scene *s, int idx, t_rect *rc, t_aabb raabb,
		t_contact *c, int count, int max);


int	query_pyramid(t_scene *s, int idx, t_contact *c, int count, int max);
int	pyramid_vs_plane(t_pyramid *py, t_plane *pl, t_contact *c, int max_c);

int	query_box(t_scene *s, int idx, t_contact *c, int count, int max);
int	box_vs_plane(t_box *bx, t_plane *pl, t_contact *c, int max_c);
int	box_vs_others(t_scene *s, int idx, t_box *bx, t_aabb baabb, t_contact *c,
		int count, int max);

int	query_capsule(t_scene *s, int idx, t_contact *c, int count, int max);
int	cap_vs_others(t_scene *s, int idx, t_capsule *cap, t_aabb caabb,
		t_contact *c, int count, int max);
int	capsule_plane_contacts(t_scene *s, t_capsule *cap, t_gjk_shape *sa,
		t_contact *c, int count, int max);

int	query_tri(t_scene *s, int idx, t_contact *c, int count, int max);
int	tri_vs_plane(t_tri_shape *tr, t_plane *pl, t_contact *c, int max_c);
int	tri_vs_others(t_scene *s, int idx, t_tri_shape *tr, t_aabb taabb,
		t_contact *c, int count, int max);

int	query_cylinder(t_scene *s, int idx, t_contact *c, int count, int max);
int	cyl_vs_others(t_scene *s, int idx, t_cylinder *cy, t_aabb cyaabb,
		t_contact *c, int count, int max);
int	cyl_plane_contacts(t_scene *s, t_cylinder *cy, t_gjk_shape *sa,
		t_contact *c, int count, int max);


int	gjk_vs_all_planes(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
		t_scene *s, t_contact *c, int count, int max);

/* DBVT Broadphase */
void	collect_leaves(struct s_scene *s, t_dbvt *t);
int		dbvt_build_range(t_dbvt *t, int begin, int end);
int		dbvt_query_pairs(t_dbvt *t, t_body_pair *out, int max);
void	build_dbvt(struct s_scene *s, t_dbvt *t);
int		narrow_dispatch(t_dbvt_leaf *a, t_dbvt_leaf *b,
			t_contact *c, int count);


/* Shape Integration */


void	integrate_sphere(struct s_sphere *sp, double dt);
void	integrate_rect(struct s_rect *rc, double dt);
void	integrate_pyramid(struct s_pyramid *py, double dt);
void	integrate_box(struct s_box *bx, double dt);
void	integrate_capsule(struct s_capsule *cap, double dt);
void	integrate_tri(struct s_tri_shape *tr, double dt);
void	integrate_cylinder(struct s_cylinder *cy, double dt);


/*
** GJK simplex — up to 4 points in Minkowski-difference space.

** a_pts / b_pts track the original support points on each shape
** (needed by EPA for barycentric contact interpolation).
*/
typedef struct s_simplex
{
	t_vec3	pts[4];
	t_vec3	a_pts[4];
	t_vec3	b_pts[4];
	int		n;
}	t_simplex;

# define EPA_MAX_ITER 30
# define EPA_MAX_FACES 64
# define EPA_MAX_VERTS 32
# define EPA_TOL 1e-5

typedef struct s_epa_face
{
	int		idx[3];
	t_vec3	normal;
	double	dist;
}	t_epa_face;

typedef struct s_epa_poly
{
	t_vec3		pts[EPA_MAX_VERTS];
	t_vec3		a_pts[EPA_MAX_VERTS];
	t_vec3		b_pts[EPA_MAX_VERTS];
	int			n_verts;
	t_epa_face	faces[EPA_MAX_FACES];
	int			n_faces;
}	t_epa_poly;

typedef struct s_edge
{
	int	a;
	int	b;
}	t_edge;

typedef struct s_epa_res
{
	t_vec3		normal;
	double		depth;
	t_vec3		contact_a;
	t_vec3		contact_b;
	void		*f;
}	t_epa_res;

/* Support functions (one per shape type) */
t_vec3	gjk_support_sphere(const void *data, t_vec3 dir);
t_vec3	gjk_support_box(const void *data, t_vec3 dir);
t_vec3	gjk_support_capsule(const void *data, t_vec3 dir);
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir);
t_vec3	gjk_support_rect(const void *data, t_vec3 dir);
t_vec3	gjk_support_tri(const void *data, t_vec3 dir);
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir);
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir);
t_vec3	gjk_support_list(const t_vec3 *v, int n, t_vec3 dir);

/* GJK Internals */
bool	simplex_line(t_simplex *s, t_vec3 *dir);
bool	simplex_triangle(t_simplex *s, t_vec3 *dir);
bool	simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
void	update_simplex3(t_simplex *s, int i0, int i1, int i2);
t_vec3	md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir,
			t_vec3 *pa, t_vec3 *pb);

/* GJK intersection test — fills 'out' simplex for EPA */
bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out);


/* EPA Internals */
t_epa_face	make_face(t_epa_poly *p, int i0, int i1, int i2);
t_vec3		bary(const t_vec3 tri[3], t_vec3 p);
void		init_polytope(t_epa_poly *p, t_simplex *s);
int			closest_face(t_epa_poly *p);
void		collect_silhouette(t_epa_poly *p, t_vec3 pt, t_edge *edges, int *n);
void		get_contact_points(t_epa_poly *poly, t_epa_face *f,
				t_vec3 *ca, t_vec3 *cb);

/* EPA — extracts MTD from GJK simplex */
bool	gjk_epa(t_gjk_shape *a, t_gjk_shape *b, t_simplex *s, t_epa_res *res);



/* Contact generation */
int		gjk_make_contact(t_gjk_shape *sa, t_gjk_shape *sb,
			t_physics_body *ba, t_physics_body *bb,
			t_transform *ta, t_transform *tb,
			t_contact *c);

int		gjk_vs_plane(t_gjk_shape *sa, t_physics_body *ba, t_transform *ta,
			t_plane *pl, t_contact *c);

/* Solver Utils */
double	get_inv_mass(t_physics_body *body);
t_vec3	point_vel(t_physics_body *body, t_vec3 r);
double	ang_term(t_physics_body *body, t_vec3 r, t_vec3 dir, double inv_m);
void	apply_solver_torque(t_physics_body *body, t_vec3 r, t_vec3 imp,
			double inv_m, double sign);

/* Velocity Solver */
double	solve_one_velocity(t_contact *ct, double inv_a, double inv_b);
void	apply_friction(t_contact *ct, double inv_a, double inv_b, t_vec3 rel_v);

/* Position Solver */
void	apply_position_correction(t_contact *ct, double inv_a, double inv_b);

/* Solver Entries */
void    solve_velocities(t_contact *contacts, int count);
void    solve_positions(t_contact *contacts, int count);


/* Utils */
double  clamp_d(double v, double lo, double hi);


#endif
