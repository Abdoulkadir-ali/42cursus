/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstget.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:15:53 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 17:22:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_nodes	*ft_lstget(t_nodes *lst, size_t g)
{
	size_t	i;

	if (!lst)
		return (NULL);
	if (g >= lst->size)
		return (NULL);
	i = 0;
	while (i < g && lst)
	{
		lst = lst->next;
		i++;
	}
	if (i == g && lst)
		return (lst);
	return (NULL);
}
