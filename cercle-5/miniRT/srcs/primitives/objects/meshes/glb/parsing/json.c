/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:34:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

/**
 * Safely extracts an integer from a JSON object item, with fallback to -1.
 */
int	json_get_int(t_json_value *obj, const char *name)
{
	t_json_value	*v;

	v = json_get(obj, name);
	if (!v)
		return (-1);
	return ((int)json_as_number(v));
}

/**
 * Public wrapper for the internal JSON integer extractor.
 */
int	glb_get_json_int(t_json_value *obj, const char *name)
{
	return (json_get_int(obj, name));
}
