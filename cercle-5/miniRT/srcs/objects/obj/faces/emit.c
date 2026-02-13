/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   faces_emit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

void	obj_face_emit_tris(t_obj_ctx *ctx, t_obj_face *face)
{
	int	i;

	i = 1;
	while (i < face->count - 1)
	{
		obj_add_vert(ctx, face->vi[0], face->vti[0], face->vni[0]);
		obj_add_vert(ctx, face->vi[i], face->vti[i], face->vni[i]);
		obj_add_vert(ctx, face->vi[i + 1], face->vti[i + 1], face->vni[i + 1]);
		i++;
	}
}
