/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 04:59:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_putnbr(size_t n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

/**
 * @brief Print the status message for a philosopher in a thread-safe way.
 * @param philo Pointer to the philosopher struct.
 * @param msg Status message to print (e.g., "is eating", "died").
 *
 * Prints the timestamp, philosopher ID,
	and status message. Sets the dead_flag if the message indicates death.
 * Locks the dead_lock mutex to ensure output consistency across threads.
 */
void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->rules->dead_lock);
	if (!philo->rules->dead_flag)
	{
		time = now() - philo->sim_start;
		ft_putnbr(time);
		write(1, " ", 1);
		ft_putnbr(philo->id);
		write(1, " ", 1);
		ft_putstr_fd(msg, 1);
		write(1, "\n", 1);
		if (msg[0] == 'd')
			philo->rules->dead_flag = 1;
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
}
