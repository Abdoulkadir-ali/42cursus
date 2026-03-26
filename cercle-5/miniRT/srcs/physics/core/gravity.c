/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot <dev@local>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 10:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

/*
 * Return the project gravity as a t_vec3.
 * Keeps a single authoritative scalar `GRAVITY` in headers and presents
 * a `gravity_vec()` convenience macro that expands to this function call.
 */
t_vec3	gravity_vec()(void)
{
    return ((t_vec3){0.0, GRAVITY, 0.0, 0.0});
}
