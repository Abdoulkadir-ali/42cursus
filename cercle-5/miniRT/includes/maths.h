/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:44:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:24:07 by abdoali          ###   ########.fr       */
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
size_t		flatten_index(t_index *dim, t_index *i);
t_index		*flat_to_index(t_index *dim, size_t flat_index);
void		print_index(t_index *i);

bool		check_dimensions(t_index *dim);

t_matrix	*create_matrix(t_index *dim, size_t elem_size);
void		create_event(t_iterate_events *events, void (*on_new_row)(void),
				void (*on_new_line)(void));
void		matrix_iterate(t_matrix *m, void (*f)(void *),
				t_iterate_events *events);
void		print_matrix(t_matrix *m, void (*f)(void *));
void		print_double(void *v);
void		print_float(void *v);
void		*get_offset(const t_matrix *m, size_t i);
bool		check_multiply(const t_matrix *m1, const t_matrix *m2);
bool		check_add(const t_matrix *m1, const t_matrix *m2);
bool		matrix_op(t_matrix *m1, const t_matrix *m2,
				bool (*check)(const t_matrix *, const t_matrix *),
				bool (*f)(void *, const void *));
bool		matrix_divide(t_matrix *m1, const t_matrix *m2, bool (*f)(void *,
					const void *));
bool		matrix_multiply(t_matrix *m1, const t_matrix *m2, bool (*f)(void *,
					const void *));
bool		cmp_indexes(t_index *i1, t_index *i2);
bool		is_same_x(t_index *i1, t_index *i2);
bool		is_same_y(t_index *i1, t_index *i2);
bool		is_same_indexes(t_index *i1, t_index *i2);
bool		is_same_index_to_val(t_index *i1, size_t v);
void		*matrix_get(const t_matrix *m, t_index *i);
bool		matrix_set(t_matrix *m, t_index *i, void *new);
void		matrix_transpose(t_matrix **m);
void		matrix_destroy(t_matrix *m);
bool		matrix_for_each(t_matrix *m, bool (*f)(void *));
void		free_matrix(t_matrix *m);
bool		matrix_add_scalar(t_matrix *m, void *v, bool (*f)(void *,
					const void *));
/* view / camera transforms */
t_matrix	*make_view_matrix(double pos[3], double orient[3], double up[3]);
t_matrix	*make_view_matrix_inverse(double pos[3], double orient[3],
				double up[3]);

int			*to_int(const char *s);
double		*to_double(const char *s);
float		*to_float(const char *s);

#endif