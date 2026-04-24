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
	INT_CYL,
	INT_PYR,
	INT_RECT,
	INT_CAP
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

#define GJK_MAX_ITER 32
/* Global State Access */

void    phys_debug_spheres(t_scene *scene);

/* Integration */
void    update_physics(t_scene *scene, t_physic_engine *engine, double dt);
void    integrate_bodies_worker(t_scene *scene, t_physic_engine *engine, double dt);
size_t  generate_contacts(t_scene *scene, t_physic_engine *engine, t_contact *contacts, size_t max_c);
void	apply_attractor_pass(t_scene *scene, t_physics_settings *s);
void	apply_nbody_gravity(t_scene *scene, double big_g);
void	apply_wind_pass(t_scene *scene, t_physics_settings *s, double dt);
void	apply_pair_grav(t_physics_body *a, t_physics_body *b, double big_g);
void	apply_pair_mag(t_physics_body *a, t_physics_body *b);
void	sync_phys_settings(t_scene *scene, t_physic_engine *engine);
void	bvh_sync(t_scene *scene);

/* Thermal System */
void	phys_heat_viscous(t_physics_body *b, double dt);
void	phys_cool_radiative(t_physics_body *b, double dt);
void	phys_heat_collision(t_contact *ct, double j, double e);
void	sync_thermal_to_materials(t_scene *scene);

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
bool	aabb_v_sphere_sq(t_aabb a, t_vec3 center, double radius_sq);
void	init_phys_pool(t_physic_engine *engine);
void	destroy_phys_pool(t_physic_engine *engine);

/* Soft Body */
bool	soft_body_build(t_soft_body *sb, t_mesh *mesh, t_sb_params p);
void	soft_body_step(t_scene *scene, double dt, t_physics_settings *s);
void	soft_body_jiggle(t_scene *scene);
void	soft_body_free(t_soft_body *sb);
bool	scene_build_soft_body(t_scene *scene, t_sb_params p);
void	soft_body_build_springs(t_soft_body *sb, t_mesh *mesh,
			size_t p_count);
void	fill_particles(t_sb_particle *out, const t_mesh *mesh,
			size_t count, t_vec3 offset);
void	apply_one_body_to_sb(t_soft_body *sb, t_vec3 body_pos,
			double g_mass);
void	apply_vols_to_sb(t_soft_body *sb, t_scene *sc, double big_g);
void	apply_surfs_to_sb(t_soft_body *sb, t_scene *sc, double big_g);
void	accumulate_ext_f(t_soft_body *sb, const t_physics_settings *s);
void	accumulate_spring_f(t_soft_body *sb);

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

t_gjk_shape		init_gjk_shape(const void *data, t_support_fn support,
			t_vec3 center);
t_contact_query	init_contact_query(t_physic_engine *engine,
			t_contact *contacts, size_t count, size_t max);
t_edge			init_edge(size_t a, size_t b);

/* GJK Internal Helpers (modular structure) */
bool	gjk_simplex_line(t_simplex *s, t_vec3 *dir);
bool	gjk_simplex_triangle(t_simplex *s, t_vec3 *dir);
bool	gjk_simplex_tetrahedron(t_simplex *s, t_vec3 *dir);
t_vec3	md_support(t_gjk_shape *a, t_gjk_shape *b, t_vec3 dir, t_simplex *s);
void	set_simplex3(t_simplex *s, size_t *i, t_vec3 *p);
void	reorder_simplex(t_simplex *s);

/* EPA — extracts MTD from GJK simplex */
bool	gjk_epa(t_col_pair *p, t_simplex *s, t_epa_res *res);

/* EPA Internal Helpers (modular structure) */
t_epa_face	epa_make_face(t_epa_poly *p, t_vec3s tri);
size_t		epa_closest_face(t_epa_poly *p);
void		epa_init_poly(t_epa_poly *p, t_simplex *s);
void		epa_expand_poly(t_epa_poly *p, t_vec3 *v, t_edge *e, size_t n_e);
void		epa_collect_silhouette(t_epa_poly *p, t_vec3 pt, t_edge *e, size_t *n);
void		epa_interpolate(t_epa_poly *poly, t_epa_face *f, t_epa_res *res);

/* Contact generation */
bool	gjk_make_contact(t_col_pair *pair, t_contact *c);
bool	gjk_vs_plane(t_col_pair *p, t_plane *pl, t_contact *c);
bool	analytic_capsule_capsule(t_contact_query *qu,
			t_capsule *a, t_capsule *b);

/* Solver */
void	solve_velocities(t_contact *c, t_physic_engine *en, size_t count);
void	solve_positions(t_contact *contacts, t_physic_engine *engine, size_t count);

/* Velocity Solver Internal Helpers */
void	solve_one_velocity(t_contact *ct, t_physic_engine *en, double ia, double ib);
void	apply_friction(t_contact *ct, t_vec3 rel_v, double j_normal);
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
t_vec3	best_box_face_verts(t_box *bx, t_vec3 dir, t_vec3 verts[4]);
size_t	box_vs_box_manifold(t_contact_query *qu, t_box *ba,
			t_box *bb, t_contact *base);
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

/* Integrate utilities */
void	check_sleep(t_physics_body *b, double dt);
void	wake_body(t_physics_body *b);
void	clamp_accel(t_physics_body *b);
void	clamp_speed(t_physics_body *b);
t_vec3	rot_by_ang(t_vec3 v, t_vec3 w, double dt);
void	sync_phys_settings(t_scene *scene, t_physic_engine *engine);
double	value_noise3(double x, double y, double z);

void	apply_wind_vols(t_scene *sc, const t_physics_settings *s, double dt);
void	apply_wind_surfs(t_scene *sc, const t_physics_settings *s, double dt);
void	apply_wind_to_soft_bodies(t_scene *scene, const t_physics_settings *s);
void	apply_wind_to_particles(t_particle_soa *soa,
			const t_physics_settings *s, double dt);
t_vec3	wind_accel_at(t_vec3 pos, const t_physics_settings *s);
void	apply_wind_to_physics_body(t_physics_body *b,
			const t_physics_settings *s, double dt);
void	update_vel(t_contact *ct, double ia, double ib, double dj);
void	persist_contacts(t_physic_engine *en, t_contact *new_c, size_t count);
void	warm_start(t_physic_engine *en);
void	solve_all(t_physic_engine *engine);
void	clamp_all_speeds(t_scene *sc);

#endif
