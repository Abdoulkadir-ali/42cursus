#ifndef PHYSICS_H
# define PHYSICS_H

# include "core.h"
# include "maths.h"

/* Forward declarations to avoid circular includes. Concrete types
 * are included in implementation files when needed. */
typedef struct s_scene t_scene;
typedef struct s_plane t_plane;
struct s_sphere;

/* Physics types - separation of concerns: per-object body and global state */
typedef struct s_physics_body
{
	t_vec3  velocity;
	t_vec3	angular_velocity;
	t_vec3	torque;
	bool    is_static;
	double  mass;
	double  elasticity; /* 0..1 bounce factor */
	double  friction;   /* 0..1 friction coefficient */
}               t_physics_body;

typedef struct s_physics_state
{
	t_vec3          gravity;
	double          global_damping; /* velocity damping */
	double          time_scale;
	int				mesh_simplify_collision; /* 0: precise, 1: capsule approx */
}               t_physics_state;

/* Accessor for global physics state */
t_physics_state	*get_physics_state(void);

// Physics update loop
void	update_physics(t_scene *scene, double dt);
void	resolve_collisions(t_scene *scene, struct s_sphere *sp);

// Gravity simulation
void	apply_gravity(t_scene *scene, float delta_time);

// Ray refraction
// n1: incident refractive index, n2: transmitted refractive index
// Returns refracted direction, or zero vector if total internal reflection
t_vec3	refract_ray(t_vec3 incident, t_vec3 normal, float n1, float n2);

/* Collision detection helpers */
bool    detect_sphere_plane_collision(const struct s_sphere *s,
				const t_plane *pl, t_vec3 *out_normal, double *out_penetration);
bool    detect_sphere_sphere_collision(const struct s_sphere *a,
				const struct s_sphere *b, t_vec3 *out_normal, double *out_penetration);

bool    detect_sphere_mesh_collision(const struct s_sphere *s, struct s_mesh *m,
				t_vec3 *out_normal, double *out_penetration);

/* Generic collider API */
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
		double      radius;     /* for sphere */
		t_vec3      half_extents;/* for box */
		t_vec3      normal;     /* for plane (local) */
		struct {
			t_vec3 a;       /* start point (local) */
			t_vec3 b;       /* end point (local) */
			double radius;
		} capsule;
	} data;
}               t_collider;

/* Dispatch between collider types; transforms are the world transforms of the bodies. */
bool    detect_collider_collision(const t_collider *a, const t_transform *ta,
				const t_collider *b, const t_transform *tb,
				t_vec3 *out_normal, double *out_penetration);

/* Interaction */
void	physics_shoot_ray(t_scene *scene, t_ray ray, double impulse);

#endif // PHYSICS_H
