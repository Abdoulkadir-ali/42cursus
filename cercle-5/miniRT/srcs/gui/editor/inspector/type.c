/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 17:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 08:41:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

const char	*type_name_str(t_type type)
{
	if (type == TYPE_SPHERE)
		return ("Sphere");
	if (type == TYPE_PLANE)
		return ("Plane");
	if (type == TYPE_CYLINDER)
		return ("Cylinder");
	if (type == TYPE_CONE)
		return ("Cone");
	if (type == TYPE_LIGHT)
		return ("Light");
	if (type == TYPE_MESH)
		return ("Mesh");
	if (type == TYPE_TRI)
		return ("Triangle");
	if (type == TYPE_RECT)
		return ("Rectangle");
	if (type == TYPE_PYRAMID)
		return ("Pyramid");
	if (type == TYPE_BOX)
		return ("Box");
	if (type == TYPE_CAPSULE)
		return ("Capsule");
	return ("Object");
}
