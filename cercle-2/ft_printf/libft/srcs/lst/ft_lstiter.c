/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:47 by abdali            #+#    #+#             */
/*   Updated: 2025/10/17 00:27:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	int	size;

	if (!lst || !f)
		return ;
	size = ft_lstsize(lst);
	while (size)
	{
		f(lst->content);
		lst = lst->next;
		size--;
	}
}
