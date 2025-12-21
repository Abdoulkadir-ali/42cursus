/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:50:00 by abdoali          ###   ########.fr       */
/*   Updated: 2025/12/21 00:50:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "geometry.h"

t_vecu3	create_vecu3(unsigned int x, unsigned int y, unsigned int z)
{
	t_vecu3	v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
