/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bake_poll.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/11 23:59:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizations.h"

void	bake_job_poll(t_gui *gui)
{
	t_bake_job		*job;
	static size_t	last_f = (size_t) - 1;

	job = gui->render.bake_job;
	if (!job)
	{
		last_f = (size_t) - 1;
		return ;
	}
	if (!job->running && !job->done)
		return ;
	if (job->running && job->frame != last_f)
	{
		ft_print_debug("BAKING: %zu/%zu\n", job->frame, job->target);
		last_f = job->frame;
	}
	if (job->done && job->done_ts != 0)
	{
		ft_print_debug("Bake Thread Finished.\n");
		job->done_ts = 0;
	}
	if (!job->running && (now_ms() - job->done_ts > BAKE_NOTIF_MS
			|| job->done_ts == 0))
		bake_job_cancel(gui);
}
