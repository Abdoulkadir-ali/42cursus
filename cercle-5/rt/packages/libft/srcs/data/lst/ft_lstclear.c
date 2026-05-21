/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:38 by abdali            #+#    #+#             */
/*   Updated: 2026/01/11 00:47:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Deletes and frees the given node and every successor of that node.
 * @note Public library exported function.
 */
void	ft_lstclear(t_nodes **lst, void (*del)(void *))
{
	t_nodes	*current;
	t_nodes	*next;
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
