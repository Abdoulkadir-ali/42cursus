/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:26:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Swap the filename payloads stored in two list nodes.
 * @param a First node participating in the swap.
 * @param b Second node participating in the swap.
 * @return This function does not return a value.
 */
static void	swap_contents(t_nodes *a, t_nodes *b)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

/**
 * @brief Sort a filename list in locale-aware lexical order.
 * @param list Address of the linked list head to reorder in place.
 * @return This function does not return a value.
 */
void	sort_list(t_nodes **list)
{
	t_nodes	*i;
	t_nodes	*j;

	i = *list;
	while (i)
	{
		j = i->next;
		while (j)
		{
			if (strcoll((char *)i->content, (char *)j->content) > 0)
				swap_contents(i, j);
			j = j->next;
		}
		i = i->next;
	}
}
