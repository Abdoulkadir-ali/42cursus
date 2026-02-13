/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faces_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	obj_face_init(t_obj_face *face)
{
	face->count = 0;
}

void	obj_face_read(t_parser *p, t_obj_face *face)
{
	while (face->count < 32)
	{
		parser_skip_spaces(p);
		if (!parser_peek(p) || parser_peek(p) == '\n')
			break ;
		face->vi[face->count] = parse_int(p);
		face->vti[face->count] = 0;
		face->vni[face->count] = 0;
		if (parser_peek(p) == '/')
			obj_face_read_slash(p, face);
		face->count++;
	}
}

void	obj_face_read_slash(t_parser *p, t_obj_face *face)
{
	parser_advance(p);
	if (parser_peek(p) != '/')
		face->vti[face->count] = parse_int(p);
	if (parser_peek(p) == '/')
	{
		parser_advance(p);
		face->vni[face->count] = parse_int(p);
	}
}
