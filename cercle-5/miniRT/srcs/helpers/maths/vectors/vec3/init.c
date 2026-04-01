/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:07:05 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:07:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 0.0});
}

t_vec3	vec3_pt(double x, double y, double z)
{
	return ((t_vec3){x, y, z, 1.0});
}

