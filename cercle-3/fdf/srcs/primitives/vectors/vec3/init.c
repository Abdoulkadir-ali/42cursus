/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:28:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Construct a 3D integer vector.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 * @return Packed `t_vec3` value.
 */
t_vec3	create_vec3(int x, int y, int z)
{
	return ((t_vec3){x, y, z});
}
