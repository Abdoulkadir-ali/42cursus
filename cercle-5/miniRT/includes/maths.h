/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/16 17:14:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "core.h"
# include "debug.h"


typedef struct s_quadratic			t_quadratic;
typedef struct s_quadratic_roots	t_quadratic_roots;

struct s_vec2
{
	double				x;
	double				y;
};

struct s_vec3
{
	double				x;
	double				y;
	double				z;
	double				w;
};

struct s_mat4
{
	double				m[4][4];
};

struct		s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	t_vec3	inv_dir;
	int		sign[3];
	int		depth;
};

struct s_aabb
{
	t_vec3				min;
	t_vec3				max;
};

struct s_rotator
{
	double				pitch;
	double				yaw;
	double				roll;
};

struct s_transform
{
	t_vec3				pos;
	t_rotator			rotation;
	t_vec3				scale;
	t_vec3				forward;
	t_vec3				right;
	t_vec3				up;
};

struct s_quadratic
{
	double				a;
	double				b;
	double				c;
};

struct s_quadratic_roots
{
	double				t1;
	double				t2;
};



/* vec2 */
t_vec2		vec2(double x, double y);
t_vec2		vec2_pt(double x, double y);
t_vec2		vec2_add(t_vec2 a, t_vec2 b);
t_vec2		vec2_sub(t_vec2 a, t_vec2 b);
t_vec2		vec2_mul(t_vec2 a, t_vec2 b);
t_vec2		vec2_scale(t_vec2 a, double s);
double		vec2_dot(t_vec2 a, t_vec2 b);
double		vec2_mag_sq(t_vec2 a);
double		vec2_mag(t_vec2 a);
t_vec2		vec2_norm(t_vec2 a);

/* vec3 */
t_vec3		vec3(double x, double y, double z);
t_vec3		vec3_pt(double x, double y, double z);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_sub(t_vec3 a, t_vec3 b);
t_vec3		vec3_mul(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 a, double s);
double		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_cross(t_vec3 a, t_vec3 b);
double		vec3_mag_sq(t_vec3 a);
double		vec3_mag(t_vec3 a);
t_vec3		vec3_norm(t_vec3 a);
t_vec3		vec3_lerp(t_vec3 a, t_vec3 b, double t);
t_vec3		vec3_min(t_vec3 a, t_vec3 b);
t_vec3		vec3_max(t_vec3 a, t_vec3 b);
bool		vec3_compare(t_vec3 a, t_vec3 b);
void		vec3_orthonormal_basis(t_vec3 normal, t_vec3 *tangent,
				t_vec3 *bitangent);
t_vec3		get_camera_forward(double pitch, double yaw);
t_vec3		rotate_vector(t_vec3 v, double pitch, double yaw);


/* mat4 */
t_mat4		mat4_mul(t_mat4 a, t_mat4 b);
t_mat4		mat4_identity(void);
t_vec3		mat4_mul_vec3(t_mat4 m, t_vec3 v);
t_mat4		mat4_scale_inplace(t_mat4 m, double s);
t_mat4		mat4_add(t_mat4 a, t_mat4 b);
t_mat4		mat4_translation(t_vec3 v);
t_mat4		mat4_scaling(t_vec3 v);
t_mat4		mat4_rotation(t_rotator r);
t_mat4		mat4_transform(t_transform t);
t_mat4		mat4_inverse_transform(t_transform t);
t_vec3		mat4_mul_pos(t_mat4 m, t_vec3 v);

t_vec3      vec3_reflect(t_vec3 I, t_vec3 N);
t_vec3      vec3_refract(t_vec3 I, t_vec3 N, double ior);


/* Roots */
bool					solve_quadratic(t_quadratic q,
							t_quadratic_roots *roots);

#endif
