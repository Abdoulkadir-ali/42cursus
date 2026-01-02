/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 02:14:42 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/02 14:37:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	ft_putnbr(size_t n)
{
	char	c;

	if (n >= 10)
		ft_putnbr(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

void	print_status(t_philo *p, char *msg)
{
	sem_wait(p->rules->print);
	ft_putnbr(now() - p->sim_start);
	write(1, " ", 1);
	ft_putnbr(p->id);
	write(1, " ", 1);
	ft_putstr_fd(msg, 1);
	write(1, "\n", 1);
	if (msg[0] != 'd')
		sem_post(p->rules->print);
}
