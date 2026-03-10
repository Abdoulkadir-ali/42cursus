/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:05:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * philo_sleep - Handles philosopher sleeping routine.
 * @philo: Pointer to philosopher struct.
 *
 * Prints sleeping status and sleeps for the configured duration.
 */
void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	precise_usleep(philo->rules->time_to_sleep);
}
