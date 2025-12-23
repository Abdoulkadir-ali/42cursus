/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 11:58:16 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 23:12:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

int	normalize_angle(double radians)
{
	int	degrees;

	degrees = (int)(radians * 180.0 / M_PI);
	degrees = degrees % 360;
	if (degrees < 0)
		degrees += 360;
	return (degrees);
}
