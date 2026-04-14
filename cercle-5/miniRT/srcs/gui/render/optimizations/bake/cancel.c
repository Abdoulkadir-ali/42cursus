/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bake_cancel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 23:58:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

static void	bake_free_internal(t_bake_job *job)
{
	free(job->accum_r);
	free(job->accum_g);
	free(job->accum_b);
	free(job->pixel_scratch);
	free(job);
}

void	bake_job_cancel(t_gui *gui)
{
	t_bake_job	*job;

	job = gui->render.bake_job;
	if (!job)
		return ;
	job->cancel = true;
	pthread_join(job->thread, NULL);
	if (job->scene_snap)
	{
		bvh_destroy(job->scene_snap->bvh);
		pthread_rwlock_destroy(&job->scene_snap->bvh_lock);
		free(job->scene_snap);
	}
	bake_free_internal(job);
	gui->render.bake_job = NULL;
}
