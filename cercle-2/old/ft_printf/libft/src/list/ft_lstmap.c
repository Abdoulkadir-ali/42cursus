/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 09:27:14 by abdali            #+#    #+#             */
/*   Updated: 2025/10/16 21:17:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*setnl;
	t_list	*tmp;

	if (!lst || !f || !del)
		return (NULL);
	newl = ft_lstnew(f(lst->content));
	if (!newl)
		return (NULL);
	setnl = newl;
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&newl, del);
			return (NULL);
		}
		setnl->next = tmp;
		setnl = tmp;
		lst = lst->next;
	}
	return (newl);
}
