/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_last.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:18:43 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 16:18:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_nodes	*ft_last(t_nodes *lst)
{
	int	size;

	if (!lst)
		return (NULL);
	size = ft_size(lst);
	while (size > 1)
	{
		lst = lst->next;
		size--;
	}
	return (lst);
}
