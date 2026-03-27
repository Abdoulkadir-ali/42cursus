/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 20:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/27 10:44:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loader.h"

bool	rt_parse_loop(t_scene *scene, t_parser *p)
{
	char	id[16];
	bool	success;

	success = true;
	while (rt_parse_token(p, id, sizeof(id)))
	{
		if (!dispatch_scan(scene, p, id))
			success = false;
	}
	return (success);
}
