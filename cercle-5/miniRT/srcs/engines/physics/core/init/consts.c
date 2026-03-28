/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:02:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 12:57:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
 * Return the project gravity as a t_vec3.
 * Keeps a single authoritative scalar `GRAVITY` in headers and presents
 * a `gravity_vec()` convenience function.
 */
t_vec3	gravity_vec(void)
{
	return ((t_vec3){0.0, GRAVITY, 0.0, 0.0});
}
