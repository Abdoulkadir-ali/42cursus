/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:43:46 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 20:33:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_puterr(char *str)
{
	ft_putstr_fd(str, 2);
	return (1);
}

void	ft_puterr_exit(char *str)
{
	ft_puterr(str);
	exit(1);
}
