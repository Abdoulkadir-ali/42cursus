/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   think.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:06:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * philo_think - Handles philosopher thinking routine.
 * @philo: Pointer to philosopher struct.
 *
 * Prints thinking status. For odd philosopher counts, 
 * waits extra time to balance routine.
 */
void	philo_think(t_philo *philo)
{
	print_status(philo, "is thinking");
	if (philo->rules->nb_philo % 2 != 0)
		precise_usleep((philo->rules->time_to_eat * 2)
			- philo->rules->time_to_sleep);
}
