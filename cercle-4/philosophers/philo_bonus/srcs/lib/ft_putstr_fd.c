/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 11:14:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 05:05:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

/**
 * ft_putstr_fd - Writes a string to a file descriptor.
 * @s: String to write.
 * @fd: File descriptor to write to.
 *
 * If s is NULL, does nothing. Uses ft_strlen to determine length.
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
