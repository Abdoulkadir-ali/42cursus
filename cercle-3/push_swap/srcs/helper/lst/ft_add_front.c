/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_front.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:18:28 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 16:18:29 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_add_front(t_nodes **lst, t_nodes *new)
{
	t_nodes	*last;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		new->next = new;
		return ;
	}
	last = ft_last(*lst);
	new->next = *lst;
	last->next = new;
	*lst = new;
}
