/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:51:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_plane(char *line)
{
	t_object	*obj;
	t_nodes	*split;
	t_matrix	*pos;
	t_matrix	*normal;
	t_matrix	*rgb;

	split = ft_split_nodes(line, " ", &any_match);
	if (!split || !validate_line_nodes(split->next, get_format_by_type(PLANE)))
	{
		ft_lstclear(&split, free);
		return (NULL);
	}
	obj = create_object();
	obj->type = PLANE;
	pos = create_matrix(create_index(3, 1), sizeof(double));
	if (!pos || !parse_vector(pos, ft_nodes_get(split, 1), to_double))
	{
		free_matrix(pos, NULL);
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	normal = create_matrix(create_index(3, 1), sizeof(double));
	if (!normal || !parse_normal_to_matrix(normal, ft_nodes_get(split, 2), &parse_float))
	{
		free_matrix(pos, NULL);
		free_matrix(normal, NULL);
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	{
		t_matrix *new_rgb;

		new_rgb = create_matrix(create_index(3, 1), sizeof(double));
		if (!new_rgb || !parse_rgb(new_rgb, ft_nodes_get(split, 3), (bool (*)(const char *))is_valid_int))
		{
			free_matrix(pos, NULL);
			free_matrix(normal, NULL);
			free_matrix(new_rgb, NULL);
			ft_lstclear(&split, free);
			destroy_object(obj);
			return (NULL);
		}
		free_matrix(obj->rgb, NULL);
		obj->rgb = new_rgb;
	}
	if (obj->transform)
	{
		free_matrix(obj->transform->pos, NULL);
		obj->transform->pos = pos;
		free_matrix(obj->transform->rotation, NULL);
		obj->transform->rotation = normal;
	}
	else
	{
		obj->transform = init_transform();
		obj->transform->pos = pos;
		free_matrix(obj->transform->rotation, NULL);
		obj->transform->rotation = normal;
	}
	ft_lstclear(&split, free);
	return (obj);
}
