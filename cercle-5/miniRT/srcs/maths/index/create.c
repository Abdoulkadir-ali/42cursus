/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 17:54:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/27 19:10:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_index	*create_index(size_t x, size_t y)
{
	t_index	*i;

	i = malloc(sizeof(t_index));
	if (!i)
		return (NULL);
	i->x = x;
	i->y = y;
	return (i);
}
