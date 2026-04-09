/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 20:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dispatcher.h"

t_parse_obj	init_none(void)
{
	t_parse_obj	obj;

	obj.type = TYPE_NONE;
	return (obj);
}

t_parse_obj	dispatch_scan(t_parser *p, char *id)
{
	t_parse_obj	obj;

	if (!id || !*id)
		return (init_none());
	obj = dispatch_basic(p, id);
	if (obj.type != TYPE_NONE)
		return (obj);
	obj = dispatch_shapes(p, id);
	if (obj.type != TYPE_NONE)
		return (obj);
	obj = dispatch_meshes(p, id);
	if (obj.type != TYPE_NONE)
		return (obj);
	return (dispatch_modifiers(p, id));
}
