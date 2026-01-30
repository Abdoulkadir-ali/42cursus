/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddback.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:30 by abdali            #+#    #+#             */
/*   Updated: 2026/01/30 17:37:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_nodes **lst, t_nodes *new)
{
	t_nodes	*last;

	if (!lst || !new)
		return ;
	new->next = NULL;
	new->size = 1;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	(*lst)->size += 1;
	last = ft_lstlast(*lst);
	last->next = new;
}
