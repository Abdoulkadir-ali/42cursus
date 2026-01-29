/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transpose.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 03:58:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 05:17:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	matrix_transpose(t_matrix **m)
{
	t_matrix	*old;
	t_matrix	*res;
	t_index		idx;
	t_index		new_idx;
	void		*src;

	if (!m || !*m || !(*m)->v)
		return ;
	old = *m;
	res = create_matrix(create_index(old->dim->y, old->dim->x), old->elem_size);
	if (!res)
		return ;
	idx.y = 0;
	while (idx.y < old->dim->y)
	{
		idx.x = 0;
		while (idx.x < old->dim->x)
		{
			new_idx.x = idx.y;
			new_idx.y = idx.x;
			src = matrix_get(old, &idx);
			matrix_set(res, &new_idx, src);
			idx.x++;
		}
		idx.y++;
	}
	matrix_destroy(*m);
	*m = res;
}
