/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   body.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "parser.h"
#include "physics.h"

static t_physics_body	parse_phys(t_json_value *obj)
{
	t_physics_body	b;

	ft_memset(&b, 0, sizeof(t_physics_body));
	b.mass = json_as_number(json_get(obj, "mass"));
	b.elasticity = json_as_number(json_get(obj, "elasticity"));
	b.friction = json_as_number(json_get(obj, "friction"));
	b.is_static = json_as_bool(json_get(obj, "static"));
	b.is_compound = true;
	if (b.mass < 1e-9)
		b.mass = 1.0;
	b.inv_inertia = vec3(1.0 / b.mass, 1.0 / b.mass, 1.0 / b.mass);
	return (b);
}

static size_t	load_bricks(t_json_value *arr, t_sub_shape *bricks, size_t max)
{
	size_t	i;

	if (!arr || arr->type != JSON_ARRAY)
		return (0);
	i = 0;
	while (i < arr->u.array.count && i < max)
	{
		bricks[i] = parse_brick(arr->u.array.elements[i]);
		i++;
	}
	return (i);
}

/**
 * @brief Parses a compound body JSON object and calls init_compound.
 * Expects: { "mass", "elasticity", "friction", "static", "bricks": [...] }
 */
t_physics_body	parse_compound_body(t_json_value *obj)
{
	t_sub_shape		bricks[MAX_SUB_SHAPES];
	t_physics_body	body;
	size_t			n;

	body = parse_phys(obj);
	n = load_bricks(json_get(obj, "bricks"), bricks, MAX_SUB_SHAPES);
	if (n > 0)
		init_compound(&body, bricks, n);
	return (body);
}
