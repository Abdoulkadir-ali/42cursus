/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 10:17:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "debug.h"

static bool	dispatch_basic(t_rt_buf *buf, t_parser *p, char *id)
{
	if (id[0] == 'A' && id[1] == '\0')
		return (parse_ambient(buf, p));
	if (id[0] == 'C' && id[1] == '\0')
		return (parse_camera(buf, p));
	if (id[0] == 'L' && id[1] == '\0')
		return (parse_light(buf, p));
	return (false);
}

static bool	dispatch_shapes(t_rt_buf *buf, t_parser *p, char *id)
{
	if (id[0] == 's' && id[1] == 'p')
		return (parse_sphere(buf, p));
	if (id[0] == 's' && id[1] == 'l')
		return (parse_spot_light(buf, p));
	if (id[0] == 'p' && id[1] == 'l')
		return (parse_plane(buf, p));
	if (id[0] == 'c' && id[1] == 'y')
		return (parse_cylinder(buf, p));
	if (id[0] == 'c' && id[1] == 'n')
		return (parse_cone(buf, p));
	if (id[0] == 't' && id[1] == 'r')
		return (parse_tri_shape(buf, p));
	if (id[0] == 'r' && id[1] == 'c')
		return (parse_rect(buf, p));
	if (id[0] == 'p' && id[1] == 'y')
		return (parse_pyramid(buf, p));
	if (id[0] == 'b' && id[1] == 'x')
		return (parse_box(buf, p));
	if (id[0] == 'c' && id[1] == 'a')
		return (parse_capsule(buf, p));
	return (false);
}

static void	handle_unknown(t_parser *p)
{
	while (parser_peek(p) && parser_peek(p) != '\n')
		parser_advance(p);
}

/*
** Meshes (obj/glb) still inject directly since they have their own
** loader lifecycle. Only rt primitive shapes use the transient buf.
*/
bool	dispatch_scan(t_scene *scene, t_rt_buf *buf, t_parser *p, char *id)
{
	bool	ok;

	if (!id || !*id)
		return (false);
	ok = dispatch_basic(buf, p, id);
	if (!ok)
		ok = dispatch_shapes(buf, p, id);
	if (!ok)
		ok = dispatch_meshes(scene, p, id);
	if (!ok)
	{
		DBG_WARN_MSG(DBG_CH_PARSER, "unknown/failed id='%s'\n", id);
		handle_unknown(p);
		return (false);
	}
	DBG_TRACE_MSG(DBG_CH_PARSER, "parsed id='%s' ok\n", id);
	return (true);
}
