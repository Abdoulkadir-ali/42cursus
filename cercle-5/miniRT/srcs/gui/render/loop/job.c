/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 14:52:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	poll_map_job(t_gui *gui)
{
	t_map_job	*job;

	job = &gui->map_job;
	if (!job->active || !job->done)
		return ;
	pthread_join(job->tid, NULL);
	job->active = false;
	if (!job->entry || !job->entry->scene)
		return ;
	gui->render.next_scene = job->entry->scene;
	gui->render.next_entry = job->entry;
	gui->render.scene_swap_pending = 1;
}
