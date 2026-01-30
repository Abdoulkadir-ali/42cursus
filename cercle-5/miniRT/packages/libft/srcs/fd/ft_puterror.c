/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 22:49:16 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/28 23:00:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_puterror(char *msg)
{
	if (msg)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putendl_fd(msg, 2);
	}
	else
		ft_putendl_fd("Error", 2);
	return (1);
}
