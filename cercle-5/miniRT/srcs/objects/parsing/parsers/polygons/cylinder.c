/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:52:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static t_matrix	*alloc_vector_from_token(char *token)
{
	t_matrix	*m;

	m = create_matrix(create_index(3, 1), sizeof(double));
	if (!m)
		return (NULL);
	if (!parse_vector(m, token, to_double))
	{
		free_matrix(m, NULL);
		return (NULL);
	}
	return (m);
}

static t_matrix	*alloc_normal_from_token(char *token)
{
	t_matrix	*m;

	m = create_matrix(create_index(3, 1), sizeof(double));
	if (!m)
		return (NULL);
	if (!parse_normal_to_matrix(m, token, &parse_float))
	{
		free_matrix(m, NULL);
		return (NULL);
	}
	return (m);
}

t_object	*parse_cylinder(char *line)
{
	t_object	*obj;
	t_nodes		*split;
	t_matrix	*pos;
	t_matrix	*normal;
	t_matrix	*m;

	split = ft_split_nodes(line, " ", &any_match);
	if (!split || !validate_line_nodes(split->next,
			get_format_by_type(CYLINDER)))
	{
		ft_lstclear(&split, free);
		return (NULL);
	}
	obj = create_object();
	obj->type = CYLINDER;
	pos = alloc_vector_from_token(ft_nodes_get(split, 1));
	if (!pos)
	{
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	normal = alloc_normal_from_token(ft_nodes_get(split, 2));
	if (!normal)
	{
		free_matrix(pos, NULL);
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	{
		t_matrix *new_rgb;

		new_rgb = create_matrix(create_index(3, 1), sizeof(double));
		if (!new_rgb || !parse_rgb(new_rgb, ft_nodes_get(split, 5),
				(bool (*)(const char *))is_valid_int))
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
	/* construct scale matrix: diameter, height, 1.0 */
	m = create_matrix(create_index(3, 1), sizeof(double));
	if (!m)
	{
		free_matrix(pos, NULL);
		free_matrix(normal, NULL);
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	matrix_set(m, create_index(0, 0), &(double){parse_float(ft_nodes_get(split, 3))});
	matrix_set(m, create_index(1, 0), &(double){parse_float(ft_nodes_get(split, 4))});
	matrix_set(m, create_index(2, 0), &(double){1.0});
	if (obj->transform)
	{
		free_matrix(obj->transform->pos, NULL);
		obj->transform->pos = pos;
		free_matrix(obj->transform->rotation, NULL);
		obj->transform->rotation = normal;
		free_matrix(obj->transform->scale, NULL);
		obj->transform->scale = m;
	}
	else
	{
		obj->transform = init_transform();
		obj->transform->pos = pos;
		free_matrix(obj->transform->rotation, NULL);
		obj->transform->rotation = normal;
		free_matrix(obj->transform->scale, NULL);
		obj->transform->scale = m;
	}
	ft_lstclear(&split, free);
	return (obj);
}
