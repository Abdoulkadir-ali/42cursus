/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 19:50:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/31 09:55:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "maths.h"

# ifndef DEBUG
#  define DEBUG 1
# endif

/* Debug print: only active when compiled with -DDEBUG or DEBUG 1 */
# if DEBUG
#  define ft_print_debug(...) (printf(__VA_ARGS__), fflush(stdout))
# else
#  define ft_print_debug(...) ((void)0)
# endif

/* Maths-level Debug */
void	print_vec2(t_vec2 *v);
void	print_vec3(t_vec3 *v);
void	print_mat4(t_mat4 *m);
void	print_transform(t_transform *t);
void	print_aabb(t_aabb *b);
void	print_ray(t_ray *r);

#endif
