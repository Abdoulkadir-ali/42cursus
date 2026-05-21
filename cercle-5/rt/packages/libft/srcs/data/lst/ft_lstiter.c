/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:05:47 by abdali            #+#    #+#             */
/*   Updated: 2026/03/25 14:11:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterates the list lst and applies the function f
 * on the content of each node.
 * @note Public library exported function.
 */
void	ft_lstiter(t_nodes *lst, void (*f)(void *))
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
