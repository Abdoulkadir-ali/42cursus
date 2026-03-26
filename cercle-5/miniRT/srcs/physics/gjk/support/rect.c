/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 07:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 11:07:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"
#include "scene.h"

/**
 * @brief GJK support point for a rectangle. Uses pre-built world-space verts.
 */
t_vec3	gjk_support_rect(const void *data, t_vec3 dir)
{
	const t_rect	*rc;

	rc = (const t_rect *)data;
	return (gjk_support_list(rc->v, 4, dir));
}
