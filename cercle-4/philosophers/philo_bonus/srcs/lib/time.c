/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 23:04:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:05:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * now - Returns the current time in milliseconds.
 *
 * Uses gettimeofday to get system time and converts to ms.
 * Useful for timestamping philosopher actions.
 */
long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * precise_usleep - Sleeps for a specified number of milliseconds.
 * @ms: Milliseconds to sleep.
 *
 * Uses now() for precise timing, loops with usleep(50).
 */
void	precise_usleep(long ms)
{
	long	start;

	start = now();
	while ((now() - start) < ms)
		usleep(50);
}
