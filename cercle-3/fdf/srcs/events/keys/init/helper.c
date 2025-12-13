/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:40:57 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 12:01:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "events.h"

static long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	init_key_actions_press(t_key_maps *key_maps)
{
	ft_memset(key_maps->key_actions, 0, sizeof(key_maps->key_actions));
	set_key_actions(key_maps);
}

void	init_key_actions_release(t_key_maps *key_maps)
{
	ft_memset(key_maps->key_releases, 0, sizeof(key_maps->key_releases));
	set_key_releases(key_maps);
}

void	calculate_fps(t_events *events)
{
	long			current_time;
	t_frame_data	*f;

	f = &events->graphics->frame_data;
	current_time = get_time_ms();
	if (f->last_check == 0)
		f->last_check = current_time;
	f->frame_count++;
	if (current_time - f->last_check >= 500)
	{
		f->fps = f->frame_count;
		f->frame_count = 0;
		f->last_check = current_time;
	}
}
