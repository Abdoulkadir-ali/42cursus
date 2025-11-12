/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 18:26:26 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 18:33:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	clear_z_buffer(t_graphics *g)
{
	int	i;
	int	total;

	if (!g->window.z_buffer)
		return ;
	total = g->window.width * g->window.height;
	i = 0;
	while (i < total)
	{
		g->window.z_buffer[i] = 1e30f;
		i++;
	}
}

void	clear_image(t_graphics *g)
{
	ft_memset(g->window.main_img.img_addr, 0, g->window.height
		* g->window.main_img.img_line_len);
}