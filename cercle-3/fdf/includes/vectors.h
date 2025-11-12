/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 23:05:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

#ifndef ENABLEDEBUG
# define ENABLEDEBUG 0
#endif

# define DBG(...) if (ENABLEDEBUG) { printf(__VA_ARGS__); fflush(stdout); }

typedef struct s_vec2
{
	int				x;
	int				y;
	struct s_vec2	(*add)(struct s_vec2, struct s_vec2);
	struct s_vec2	(*sub)(struct s_vec2, struct s_vec2);
	struct s_vec2	(*multiply)(struct s_vec2, struct s_vec2);
	struct s_vec2	(*divide)(struct s_vec2, struct s_vec2);
	struct s_vec2	(*multiply_scalar)(struct s_vec2, double);
}					t_vec2;

typedef struct s_vec2d
{
	double			x;
	double			y;
	struct s_vec2d	(*add)(struct s_vec2d, struct s_vec2d);
	struct s_vec2d	(*sub)(struct s_vec2d, struct s_vec2d);
	struct s_vec2d	(*multiply)(struct s_vec2d, struct s_vec2d);
	struct s_vec2d	(*divide)(struct s_vec2d, struct s_vec2d);
	struct s_vec2d	(*multiply_scalar)(struct s_vec2d, double);
}					t_vec2d;

typedef struct s_vec3
{
	int				x;
	int				y;
	int				z;
	struct s_vec3	(*add)(struct s_vec3, struct s_vec3);
	struct s_vec3	(*sub)(struct s_vec3, struct s_vec3);
	struct s_vec3	(*multiply)(struct s_vec3, struct s_vec3);
	struct s_vec3	(*divide)(struct s_vec3, struct s_vec3);
	struct s_vec3	(*multiply_scalar)(struct s_vec3, double);
}					t_vec3;

typedef struct s_vec3d
{
	double			x;
	double			y;
	double			z;
	struct s_vec3d	(*add)(struct s_vec3d, struct s_vec3d);
	struct s_vec3d	(*sub)(struct s_vec3d, struct s_vec3d);
	struct s_vec3d	(*multiply)(struct s_vec3d, struct s_vec3d);
	struct s_vec3d	(*divide)(struct s_vec3d, struct s_vec3d);
	struct s_vec3d	(*multiply_scalar)(struct s_vec3d, double);
}					t_vec3d;

typedef struct s_point
{
	t_vec3			pos;
	int				color;
}					t_point;

# define create_vec3(x, y, z) ((t_vec3){x, y, z, vec3_add, vec3_sub, vec3_multiply, vec3_divide, vec3_multiply_scalar})
# define create_vec3d(x, y, z) ((t_vec3d){x, y, z, vec3d_add, vec3d_sub, vec3d_multiply, vec3d_divide, vec3d_multiply_scalar})

# define create_vec2(x, y) ((t_vec2){x, y, vec2_add, vec2_sub, vec2_multiply, vec2_divide, vec2_multiply_scalar})
# define create_vec2d(x, y) ((t_vec2d){x, y, vec2d_add, vec2d_sub, vec2d_multiply, vec2d_divide, vec2d_multiply_scalar})

t_vec2				vec2_add(t_vec2 self, t_vec2 other);
t_vec2				vec2_sub(t_vec2 self, t_vec2 other);
t_vec2				vec2_multiply(t_vec2 self, t_vec2 other);
t_vec2				vec2_divide(t_vec2 self, t_vec2 other);
t_vec2				vec2_multiply_scalar(t_vec2 self, double scalar);

t_vec2d				vec2d_add(t_vec2d self, t_vec2d other);
t_vec2d				vec2d_sub(t_vec2d self, t_vec2d other);
t_vec2d				vec2d_multiply(t_vec2d self, t_vec2d other);
t_vec2d				vec2d_divide(t_vec2d self, t_vec2d other);
t_vec2d				vec2d_multiply_scalar(t_vec2d self, double scalar);

t_vec3				vec3_add(t_vec3 self, t_vec3 other);
t_vec3				vec3_sub(t_vec3 self, t_vec3 other);
t_vec3				vec3_multiply(t_vec3 self, t_vec3 other);
t_vec3				vec3_divide(t_vec3 self, t_vec3 other);
t_vec3				vec3_multiply_scalar(t_vec3 self, double scalar);

t_vec3d				vec3d_add(t_vec3d self, t_vec3d other);
t_vec3d				vec3d_sub(t_vec3d self, t_vec3d other);
t_vec3d				vec3d_multiply(t_vec3d self, t_vec3d other);
t_vec3d				vec3d_divide(t_vec3d self, t_vec3d other);
t_vec3d				vec3d_multiply_scalar(t_vec3d self, double scalar);
#endif
