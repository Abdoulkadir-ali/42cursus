/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brick.c                                            :+:      :+:    :+:   */
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
#include "objects.h"

static t_vec3	json_vec3(t_json_value *obj, const char *k)
{
	t_json_value *v = json_get(obj, k);
	if (!v || v->type != JSON_ARRAY) return (vec3(0, 0, 0));
	return (vec3(
		json_as_number(json_at(v, 0)),
		json_as_number(json_at(v, 1)),
		json_as_number(json_at(v, 2))
	));
}

static t_phys_type	type_from_str(const char *s)
{
	if (!s) return (TYPE_PHYS_BOX);
	if (ft_strncmp(s, "sphere", 7) == 0) return (TYPE_PHYS_SPHERE);
	if (ft_strncmp(s, "capsule", 8) == 0) return (TYPE_PHYS_CAPSULE);
	if (ft_strncmp(s, "cylinder", 9) == 0) return (TYPE_PHYS_CYLINDER);
	if (ft_strncmp(s, "rect", 5) == 0) return (TYPE_PHYS_RECT);
	if (ft_strncmp(s, "tri", 4) == 0) return (TYPE_PHYS_TRI);
	if (ft_strncmp(s, "pyramid", 8) == 0) return (TYPE_PHYS_PYRAMID);
	return (TYPE_PHYS_BOX);
}

t_sub_shape	parse_brick(t_json_value *obj)
{
	t_sub_shape	b;
	t_json_value *v_min;

	ft_memset(&b, 0, sizeof(t_sub_shape));
	b.type = type_from_str(json_as_string(json_get(obj, "type")));
	b.offset = json_vec3(obj, "offset");
	v_min = json_get(obj, "aabb_min");
	if (v_min)
	{
		b.local_aabb.min = json_vec3(obj, "aabb_min");
		b.local_aabb.max = json_vec3(obj, "aabb_max");
	}
	else
		compute_primitive_aabb(&b);
	return (b);
}
