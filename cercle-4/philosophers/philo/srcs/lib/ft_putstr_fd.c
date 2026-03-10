/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 11:14:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 04:54:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/**
 * @brief Write string to file descriptor.
 * @param s String to write.
 * @param fd File descriptor to write to.
 *
 * Writes the string s to the file descriptor fd. Does nothing if s is NULL.
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
