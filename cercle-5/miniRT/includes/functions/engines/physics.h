#ifndef PHYSICS_H
# define PHYSICS_H

# include "scene.h"
# include "objects.h"
# include "thread.h"
# include "t_physics.h"

/* Forward declarations */
typedef struct s_collision t_collision;

typedef enum e_int_type
{
	INT_SPH,
	INT_BOX,
	INT_TRI,
	INT_CYL
}	t_int_type;

typedef struct s_int_task
{
	t_scene				*sc;
	double				dt;
	t_physics_settings	*s;
	size_t				next;
	t_int_type			type;
}	t_int_task;

typedef struct s_trav
{
	const t_bvh	*v;
	t_sphere	*sp;
	size_t		*st;
	size_t		*top;
}	t_trav;

bool	test_sphere_triangle(const t_sphere *s, t_vec3 v[3], t_collision *col);
t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 a, t_vec3 b, t_vec3 c);
bool	mesh_aabb_overlap(const t_aabb *a, const t_aabb *b);
bool	detect_sphere_capsule_collision(const t_sphere *s,
			const t_collider *c, t_collision *out);
t_aabb	sphere_aabb(const t_sphere *s);

/* ── GJK / EPA ──────────────────────────────────────────────────────────── */

#define GJK_MAX_ITER 20
/* Global State Access */

void    phys_debug_spheres(t_scene *scene);

/* Integration */
void    update_physics(t_scene *scene, t_physic_engine *engine, double dt);
void    integrate_bodies_worker(t_scene *scene, t_physic_engine *engine, double dt);
size_t  generate_contacts(t_scene *scene, t_physic_engine *engine, t_contact *contacts, size_t max_c);

/* Internal Integrators */
void	integrate_sphere(t_sphere *sp, double dt, t_physics_settings *s);
void	integrate_rect(t_rect *rc, double dt, t_physics_settings *s);
void	integrate_pyramid(t_pyramid *py, double dt, t_physics_settings *s);
void	integrate_box(t_box *bx, double dt, t_physics_settings *s);
void	integrate_capsule(t_capsule *cap, double dt, t_physics_settings *s);
void	integrate_tri(t_tri_shape *tr, double dt, t_physics_settings *s);
void	integrate_cylinder(t_cylinder *cy, double dt, t_physics_settings *s);
t_vec3	rot_by_ang(t_vec3 v, t_vec3 w, double dt);

/* Query Functions */
void	loop_boxes(t_contact_query *q, t_gjk_shape *s, t_physics_body *b,
			t_transform *t);
void	loop_capsules(t_contact_query *q, t_gjk_shape *s, t_physics_body *b,
			t_transform *t);
void	loop_cylinders(t_contact_query *q, t_gjk_shape *s, t_physics_body *b,
			t_transform *t);
void	loop_rects(t_contact_query *q, t_gjk_shape *s, t_physics_body *b,
			t_transform *t);
void	loop_tris(t_contact_query *q, t_gjk_shape *s, t_physics_body *b,
			t_transform *t);
void	loop_pyramids(t_contact_query *q, t_gjk_shape *s, t_physics_body *b,
			t_transform *t);
size_t	query_shapes(t_contact_query *query, t_gjk_shape *sa,
			t_physics_body *ba, t_transform *ta);
size_t	query_sphere(t_contact_query *qu, size_t idx);
size_t	query_box(t_contact_query *qu, size_t idx);
size_t	query_capsule(t_contact_query *qu, size_t idx);
size_t	query_cylinder(t_contact_query *qu, size_t idx);
size_t	query_rect(t_contact_query *qu, size_t idx);
size_t	query_tri(t_contact_query *qu, size_t idx);
size_t	query_pyramid(t_contact_query *qu, size_t idx);

/* BVH broadphase */
bool	bvh_resolve_ref(t_scene *s, t_bvh_ref ref, t_ref_data *d);
void	bvh_query_shapes(t_bvh_phys_ctx *c, t_aabb qa);

/* Internal Helpers */
bool	aabb_overlap(t_aabb a, t_aabb b);
bool	aabb_v_sphere(t_aabb a, t_vec3 center, double radius);
void	init_phys_pool(t_physic_engine *engine);

/* Support functions (one per shape type) */
t_vec3	gjk_support_sphere(const void *data, t_vec3 dir);
t_vec3	gjk_support_box(const void *data, t_vec3 dir);
t_vec3	gjk_support_capsule(const void *data, t_vec3 dir);
t_vec3	gjk_support_cylinder(const void *data, t_vec3 dir);
t_vec3	gjk_support_rect(const void *data, t_vec3 dir);
t_vec3	gjk_support_tri(const void *data, t_vec3 dir);
t_vec3	gjk_support_pyramid(const void *data, t_vec3 dir);
t_vec3	gjk_support_mesh(const void *data, t_vec3 dir);
bool	detect_sphere_mesh_collision(const t_sphere *s, t_mesh *m,
			t_physic_engine *en, t_collision *out);


/* GJK intersection test — fills 'out' simplex for EPA */
bool	gjk_intersect(t_gjk_shape *a, t_gjk_shape *b, t_simplex *out);

/* GJK Internal Helpers (modular structure) */
bool	gjk_simplex_line(t_simplex *s, t_vec3 *dir);
bool	gjk_simplex_triangle(t_simplex *s, t_vec3 *dir);
bool	gjk_simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
t_vec3	md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir, t_simplex *s);
void	set_simplex3(t_simplex *s, size_t *i, t_vec3 *p);

/* EPA — extracts MTD from GJK simplex */
bool	gjk_epa(t_col_pair *p, t_simplex *s, t_epa_res *res);

/* EPA Internal Helpers (modular structure) */
t_epa_face	epa_make_face(t_epa_poly *p, size_t i0, size_t i1, size_t i2);
size_t		epa_closest_face(t_epa_poly *p);
void		epa_init_poly(t_epa_poly *p, t_simplex *s);
void		epa_expand_poly(t_epa_poly *p, t_vec3 *v, t_edge *e, size_t n_e);
void		epa_collect_silhouette(t_epa_poly *p, t_vec3 pt, t_edge *e, size_t *n);
void		epa_interpolate(t_epa_poly *poly, t_epa_face *f, t_epa_res *res);

/* Contact generation */
bool	gjk_make_contact(t_col_pair *pair, t_contact *c);
bool	gjk_vs_plane(t_col_pair *p, t_plane *pl, t_contact *c);

/* Solver */
void	solve_velocities(t_contact *c, t_physic_engine *en, size_t count);
void	solve_positions(t_contact *contacts, t_physic_engine *engine, size_t count);

/* Velocity Solver Internal Helpers */
void	solve_one_velocity(t_contact *ct, t_physic_engine *en, double ia, double ib);
void	apply_friction(t_contact *ct, double inv_a, double inv_b, t_vec3 rel_v);
void	apply_phys_torque(t_physics_body *b, t_vec3 r, t_vec3 imp, double i_m_s);
double	ang_term(t_physics_body *body, t_vec3 r, t_vec3 dir, double inv_m);
t_vec3	point_vel(t_physics_body *body, t_vec3 r);
double	get_inv_mass(t_physics_body *body);

/* Utils */
double  clamp_d(double v, double lo, double hi);



size_t	pyramid_vs_planes(t_contact_query *qu, t_pyramid *py);
size_t	cylinder_vs_all_planes(t_contact_query *qu, t_col_pair *p);
size_t	box_vs_all_planes(t_contact_query *qu, t_box *bx);
size_t	rect_vs_all_planes(t_contact_query *qu, t_rect *rc);
size_t	tri_vs_all_planes(t_contact_query *qu, t_tri_shape *tr);
void	sphere_vs_sphere(t_sphere *sp, t_sphere *other, t_contact_query *q);
void	sphere_vs_mesh(t_sphere *sp, t_mesh *m, t_contact_query *q);
void	sphere_vs_plane_analytic(t_sphere *sp, t_plane *pl, t_contact_query *q);
void	traverse_sphere_bvh(t_contact_query *qu, size_t idx, t_sphere *sp);

/* Internal collision helpers */
bool	mesh_aabb_overlap(const t_aabb *a, const t_aabb *b);
bool	test_sphere_triangle(const struct s_sphere *s, t_vec3 v[3],
			t_collision *col);
t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2);
bool	detect_sphere_capsule_collision(const struct s_sphere *s,
			const t_collider *c, t_collision *out);

#endif
