/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 05:32:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 06:20:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*create_object(void)
{
	t_object	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
	{
		free_matrix(m);
		return (NULL);
	}
	obj->type = AMBIENT;
	obj->t = init_transform();
	obj->rgb = init_rgb();
	return (obj);
}
