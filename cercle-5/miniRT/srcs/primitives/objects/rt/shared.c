/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:46:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 11:59:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

int	scene_allocate_object_slot(void **ptr, size_t *count, size_t *cap, size_t sz)
{
	if (!DYNARRAY_ENSURE_INT(ptr, count, cap, sz))
		return (-1);
	return ((*count)++);
}
