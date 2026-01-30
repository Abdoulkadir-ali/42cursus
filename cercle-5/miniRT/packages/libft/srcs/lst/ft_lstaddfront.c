/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddfront.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:34 by abdali            #+#    #+#             */
/*   Updated: 2026/01/30 17:37:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_nodes **lst, t_nodes *new)
{
	if (!lst || !new)
		return ;
	if (!*lst)
	{
		new->next = NULL;
		new->size = 1;
		*lst = new;
		return ;
	}
	new->next = *lst;
	new->size = (*lst)->size + 1;
	*lst = new;
}
