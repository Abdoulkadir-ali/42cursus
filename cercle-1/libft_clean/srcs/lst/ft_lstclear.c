/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:38 by abdali            #+#    #+#             */
/*   Updated: 2025/10/17 00:27:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;
	int		size;

	if (!lst || !*lst)
		return ;
	current = *lst;
	size = ft_lstsize(current);
	while (size)
	{
		next = current->next;
		if (del)
			del(current->content);
		free(current);
		current = next;
		size--;
	}
	*lst = NULL;
}
