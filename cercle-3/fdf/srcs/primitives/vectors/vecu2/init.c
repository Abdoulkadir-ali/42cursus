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
 * @brief Construct a 2D unsigned vector.
 * @param x X component.
 * @param y Y component.
 * @return Packed `t_vecu2` value.
 */
t_vecu2	create_vecu2(unsigned int x, unsigned int y)
{
	t_vecu2	v;

	v.x = x;
	v.y = y;
	return (v);
}
