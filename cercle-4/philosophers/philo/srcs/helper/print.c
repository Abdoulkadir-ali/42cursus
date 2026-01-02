/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 02:44:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg)
{
	long	time;

	pthread_mutex_lock(&philo->rules->dead_lock);
	if (!philo->rules->dead_flag)
	{
		time = now() - philo->sim_start;
		ft_putnbr_base(time, "0123456789");
		ft_putstr_fd(" ", 1);
		ft_putnbr_base(philo->id, "0123456789");
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(msg, 1);
		ft_putstr_fd("\n", 1);
	}
	pthread_mutex_unlock(&philo->rules->dead_lock);
}
