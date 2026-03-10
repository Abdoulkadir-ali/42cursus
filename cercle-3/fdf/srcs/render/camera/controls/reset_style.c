/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_style.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:27:06 by abdoali          #+#    #+#             */
/*   Updated: 2025/12/23 14:27:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

/**
 * @brief Clear the camera color shift and restore the neutral style state.
 * @param camera Camera whose style parameters are reset.
 */
void	reset_style(t_camera *camera)
{
	if (!camera)
		return ;
	camera->color_shift.x = 0;
	camera->color_shift.y = 0;
	camera->color_shift.z = 0;
}
