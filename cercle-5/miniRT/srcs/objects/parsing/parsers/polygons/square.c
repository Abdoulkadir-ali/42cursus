/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:51:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static t_nodes	*split_and_validate(char *line)
{
	t_nodes	*split;

	split = ft_split_nodes(line, " ", &any_match);
	if (!split || !validate_line_nodes(split->next, get_format_by_type(SQUARE)))
	{
		ft_lstclear(&split, free);
		return (NULL);
	}
	return (split);
}

static t_matrix	*parse_position(char *tok)
{
	t_matrix	*pos;

	pos = create_matrix(create_index(3, 1), sizeof(double));
	if (!pos || !parse_vector(pos, tok, to_double))
	{
		free_matrix(pos, NULL);
		return (NULL);
	}
	return (pos);
}

static t_matrix	*make_size_matrix_from_token(char *tok)
{
	t_matrix	*m;
	t_index		idx;
	double		d;

	d = parse_float(tok);
	m = create_matrix(create_index(3, 1), sizeof(double));
	if (!m)
		return (NULL);
	idx.y = 0;
	for (idx.x = 0; idx.x < 3; idx.x++)
		matrix_set(m, idx, &d);
	return (m);
}

static t_matrix	*parse_rgb_matrix(char *tok)
{
	t_matrix	*rgb;

	rgb = create_matrix(create_index(3, 1), sizeof(double));
	if (!rgb || !parse_rgb(rgb, tok, (bool (*)(const char *))is_valid_int))
	{
		free_matrix(rgb, NULL);
		return (NULL);
	}
	return (rgb);
}

t_object	*parse_square(char *line)
{
	t_object	*obj;
	t_nodes		*split;
	t_matrix	*pos;
	t_matrix	*m;
	t_matrix	*rgb;

	split = split_and_validate(line);
	if (!split)
		return (NULL);
	obj = create_object();
	if (!obj)
	{
		ft_lstclear(&split, free);
		return (NULL);
	}
	obj->type = SQUARE;
	pos = parse_position(ft_nodes_get(split, 1));
	if (!pos)
	{
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	m = make_size_matrix_from_token(ft_nodes_get(split, 3));
	if (!m)
	{
		free_matrix(pos, NULL);
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	rgb = parse_rgb_matrix(ft_nodes_get(split, 4));
	if (!rgb)
	{
		free_matrix(pos, NULL);
		free_matrix(m, NULL);
		ft_lstclear(&split, free);
		destroy_object(obj);
		return (NULL);
	}
	free_matrix(obj->rgb, NULL);
	obj->rgb = rgb;
	if (obj->transform)
	{
		free_matrix(obj->transform->pos, NULL);
		obj->transform->pos = pos;
		free_matrix(obj->transform->scale, NULL);
		obj->transform->scale = m;
	}
	else
	{
		obj->transform = init_transform();
		obj->transform->pos = pos;
		free_matrix(obj->transform->scale, NULL);
		obj->transform->scale = m;
	}
	ft_lstclear(&split, free);
	return (obj);
}
