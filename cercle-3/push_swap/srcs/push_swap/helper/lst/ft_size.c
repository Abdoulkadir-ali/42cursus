/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_size.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:18:51 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 16:18:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_size(t_nodes *lst)
{
	int		count;
	t_nodes	*start;

	if (!lst)
		return (0);
	count = 0;
	start = lst;
	while (lst)
	{
		count++;
		lst = lst->next;
		if (lst == start)
			break ;
	}
	return (count);
}
