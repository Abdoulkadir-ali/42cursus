/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 21:14:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_H
# define MATHS_H

# include "libft.h"
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

/*We use 1D -> 2D  table representation*/

typedef struct s_index
{
	size_t	x;
	size_t	y;
}			t_index;

typedef struct s_iterate_events
{
	void	(*on_new_row)(void);
	void	(*on_new_line)(void);
}			t_iterate_events;

typedef struct s_matrix
{
	t_index	*dim;
	void	*v;
	size_t	elem_size;
}			t_matrix;

t_index		*create_index(size_t x, size_t y);
size_t		index_to_flat(t_index *dim, t_index *i);
t_index		*flat_to_index(t_index *dim, size_t flat_index);
void		print_index(t_index *i);

bool		check_dimensions(t_index *dim);
t_matrix	*create_matrix(t_index *dim, size_t elem_size);
void		create_event(t_iterate_events *events, void (*on_new_row)(void),
				void (*on_new_line)(void));
void		iterate_matrix(t_matrix *m, void (*f)(void *),
				t_iterate_events *events);
void		print_matrix(t_matrix *m, void (*f)(void *));
void		print_double(void *v);
void		print_float(void *v);
void		*get_offset(const t_matrix *m, size_t i);
int			check_multiply(const t_matrix *m1, const t_matrix *m2);
int			matrix_op(t_matrix *m1, const t_matrix *m2,
				int (*check)(const t_matrix *, const t_matrix *),
				int (*f)(void *, const void *));
int			matrix_divide(t_matrix *m1, const t_matrix *m2, int (*f)(void *,
					const void *));
int			matrix_multiply(t_matrix *m1, const t_matrix *m2, int (*f)(void *,
					const void *));

#endif