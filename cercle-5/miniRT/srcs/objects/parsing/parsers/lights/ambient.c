/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 04:26:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 18:49:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

t_object	*parse_ambient(char *line)
{
	t_object	*obj;
	t_nodes	*split;
	char	*tok1;
	char	*tok2;

	split = ft_split_nodes(line, " ", &any_match);
	if (!split || !validate_line_nodes(split->next, get_format_by_type(AMBIENT)))
		return (NULL);
	obj = create_object();
	tok1 = ft_nodes_get(split, 1);
	tok2 = ft_nodes_get(split, 2);
	obj->type = AMBIENT;
	/* store intensity in transform->scale[0] to be consistent with light */
	matrix_set(obj->transform->scale, create_index(0, 0), &(double){parse_float(tok1)});
	{
		t_matrix *new_rgb;

		new_rgb = create_matrix(create_index(3, 1), sizeof(double));
		if (!new_rgb || !parse_rgb(new_rgb, tok2,
				(bool (*)(const char *))is_valid_int))
		{
			free_matrix(new_rgb, NULL);
			destroy_object(obj);
			ft_lstclear(&split, free);
			return (NULL);
		}
		free_matrix(obj->rgb, NULL);
		obj->rgb = new_rgb;
	}
	ft_lstclear(&split, free);
	return (obj);
}
