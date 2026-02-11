/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:50:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/11 11:33:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_nodes **lst, int (*cmp)(void *, void *))
{
	t_nodes	*i;
	t_nodes	*j;
	void	*tmp;
	int		count;

	if (!lst || !*lst)
		return ;
	count = 0;
	i = *lst;
	while (i && count < 10000)
	{
		j = i->next;
		while (j)
		{
			if (cmp(i->content, j->content) > 0)
			{
				tmp = i->content;
				i->content = j->content;
				j->content = tmp;
			}
			j = j->next;
		}
		i = i->next;
		count++;
	}
}
