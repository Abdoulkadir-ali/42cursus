/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_back.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:18:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 21:37:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_add_back(t_nodes **lst, t_nodes *new)
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
	last->next = new;
	new->next = *lst;
}
