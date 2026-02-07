/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 18:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/07 23:40:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects/rt.h"

t_parse_obj	parse_ambient(char **tokens)
{
	t_parse_obj	res;

	res.type = TYPE_NONE;
	if (!tokens[1] || !tokens[2])
		return (res);
	
	if (!parse_float_checked(tokens[1], &res.data.ambient.brightness)
		|| !parse_color_checked(tokens[2], &res.data.ambient.rgb))
		return (res);
	
	res.type = TYPE_AMBIENT;
	return (res);
}
