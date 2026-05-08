/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pos.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 10:55:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

t_vec2	get_pw_min(t_push_wall *pw)
{
	t_vec2	min;

	min.x = (float)pw->s.x + pw->offset * (float)pw->d.x;
	min.y = (float)pw->s.y + pw->offset * (float)pw->d.y;
	return (min);
}
