/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 13:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 02:27:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "primitives.h"

/**
 * @brief Construct a 3D unsigned vector.
 * @param x X component.
 * @param y Y component.
 * @param z Z component.
 * @return Packed `t_vecu3` value.
 */
t_vecu3	create_vecu3(unsigned int x, unsigned int y, unsigned int z)
{
	t_vecu3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
