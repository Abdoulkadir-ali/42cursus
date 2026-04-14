/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   taa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 23:59:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

void	taa_apply(t_gui *gui)
{
	size_t	n;

	if (!gui->opts.taa_buf || !gui->opts.depth_buf)
		return ;
	gui->opts.taa_frame++;
	gui_parallel_task_worker(gui, TASK_TAA);
	n = (size_t)gui->win.size.x * (size_t)gui->win.size.y;
	ft_memcpy(gui->win.addr, gui->opts.taa_buf, n * sizeof(uint32_t));
}
