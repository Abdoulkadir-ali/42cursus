/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/01 23:04:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 04:59:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * @brief Get the current time in milliseconds.
 * @return Current time in milliseconds since epoch.
 *
 * Uses gettimeofday to return the time in ms for simulation timing.
 */
long	now(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

/**
 * @brief Sleep for a precise number of milliseconds.
 * @param ms Number of milliseconds to sleep.
 * Uses a busy loop with usleep(500) to ensure 
 * accurate timing for philosopher actions.
 */
void	precise_usleep(long ms)
{
	long	start;

	start = now();
	while ((now() - start) < ms)
		usleep(500);
}
