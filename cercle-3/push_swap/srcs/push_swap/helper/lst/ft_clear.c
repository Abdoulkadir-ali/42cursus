/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:18:32 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 16:18:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_clear(t_nodes **lst)
{
	t_nodes	*current;
	int		size;

	if (!lst || !*lst)
		return ;
	size = ft_size(*lst);
	while (size)
	{
		current = *lst;
		*lst = (*lst)->next;
		ft_delone(current);
		size--;
	}
	*lst = NULL;
}
