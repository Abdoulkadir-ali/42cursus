/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:21:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 15:56:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

size_t	flatten_index(t_index dim, t_index i)
{
	return (i.y * dim.x + i.x);
}

t_index	flat_to_index(t_index dim, size_t flat_index)
{
	return (create_index(flat_index % dim.x, flat_index / dim.x));
}

// int	main(void)
// {
// 	t_index	dim;
// 	size_t	j;
// 	t_index	i;

// 	dim.x = 1920;
// 	dim.y = 1080;
// 	j = 15;
// 	print_index(index_to_flat(dim, j));
// 	printf("\nis flat index of : %zu\n");
// 	i->x = 1;
// 	i->y = 0;
// 	print_index(i);
// 	printf("\nis in flat index : %zu\n", flat_to_index(dim, i));
// }
