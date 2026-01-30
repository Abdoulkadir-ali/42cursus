/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:32:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_camera(char *line)
{
	t_object	*obj;
	t_nodes		*split;
	t_matrix	*pos;
	t_matrix	*orient;
	int			fov;

	split = ft_split_nodes(line, " ", &any_match);
	if (!split || !validate_line_nodes(split->next, get_format_by_type(CAMERA)))
	{
		ft_lstclear(&split, free);
		return (NULL);
	}
	obj = create_object();
	obj->type = CAMERA;
	pos = create_matrix(create_index(3, 1), sizeof(double));
	if (!pos || !parse_vector(pos, ft_nodes_get(split, 1), to_double))
	{
		free_matrix(pos, NULL);
		ft_lstclear(&split, free);
		free(obj);
		return (NULL);
	}
	orient = create_matrix(create_index(3, 1), sizeof(double));
	if (!orient || !parse_normal_to_matrix(orient, ft_nodes_get(split, 2),
			&parse_float))
	{
		free_matrix(pos, NULL);
		free_matrix(orient, NULL);
		ft_lstclear(&split, free);
		free(obj);
		return (NULL);
	}
	fov = parse_int(ft_nodes_get(split, 3));
	(void)fov;
	if (obj->transform)
	{
		free_matrix(obj->transform->pos, NULL);
		obj->transform->pos = pos;
		free_matrix(obj->transform->rotation, NULL);
		obj->transform->rotation = orient;
	}
	else
	{
		obj->transform = init_transform();
		obj->transform->pos = pos;
		free_matrix(obj->transform->rotation, NULL);
		obj->transform->rotation = orient;
	}
	ft_lstclear(&split, free);
	return (obj);
}
