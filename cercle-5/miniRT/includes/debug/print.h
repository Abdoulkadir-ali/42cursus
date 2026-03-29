/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:46:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINT_H
# define PRINT_H

# include "maths.h"

/* --- Maths print functions (srcs/debug/print/maths.c) --- */
void	print_vec2(t_vec2 *v);
void	print_vec3(t_vec3 *v);
void	print_mat4(t_mat4 *m);
void	print_transform(t_transform *t);
void	print_aabb(t_aabb *b);

#endif
