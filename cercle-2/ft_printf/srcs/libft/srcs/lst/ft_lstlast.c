/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:52 by abdali            #+#    #+#             */
/*   Updated: 2025/10/17 00:18:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	size;

	if (!lst)
		return (NULL);
	size = ft_lstsize(lst);
	while (size > 1)
	{
		lst = lst->next;
		size--;
	}
	return (lst);
}
