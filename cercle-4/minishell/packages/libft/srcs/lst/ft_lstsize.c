/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:07 by abdali            #+#    #+#             */
/*   Updated: 2026/01/11 00:47:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_nodes *lst)
{
	t_nodes	*first;
	int		size;

	if (!lst)
		return (0);
	first = lst;
	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
		if (lst == first)
			break ;
	}
	return (size);
}
