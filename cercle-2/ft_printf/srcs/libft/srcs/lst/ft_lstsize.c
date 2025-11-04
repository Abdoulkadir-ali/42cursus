/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:07 by abdali            #+#    #+#             */
/*   Updated: 2025/10/17 00:15:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	t_list	*first;
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
