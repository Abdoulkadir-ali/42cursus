/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_getters.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:33:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

double	json_as_number(t_json_value *val)
{
	if (!val || val->type != JSON_NUMBER)
		return (0.0);
	return (val->number);
}

const char	*json_as_string(t_json_value *val)
{
	if (!val || val->type != JSON_STRING)
		return (NULL);
	return (val->string);
}
