/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:59 by abdali            #+#    #+#             */
/*   Updated: 2026/01/11 00:47:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_nodes	*ft_lstmap(t_nodes *lst, void *(*f)(void *), void (*del)(void *))
{
	t_nodes	*new_list;
	t_nodes	*new_node;
	void	*new_content;
	int		size;

	if (!lst || !f)
		return (NULL);
	new_list = NULL;
	size = ft_lstsize(lst);
	while (size > 0)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			if (del)
				del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
		size--;
	}
	return (new_list);
}
