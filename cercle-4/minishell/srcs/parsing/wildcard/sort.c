/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:38:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static size_t	max_content_len(t_nodes *a, t_nodes *b)
{
	size_t	la;
	size_t	lb;

	la = ft_strlen((char *)a->content);
	lb = ft_strlen((char *)b->content);
	if (la > lb)
		return (la);
	return (lb);
}

static bool	should_swap_nodes(t_nodes *a, t_nodes *b)
{
	size_t	cmp_len;

	cmp_len = max_content_len(a, b);
	return (ft_strncmp((char *)a->content, (char *)b->content, cmp_len
			+ 1) > 0);
}

static void	swap_node_contents(t_nodes *a, t_nodes *b)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

/**
 * @brief Sort a filename list in locale-aware lexical order using bubble sort.
 * @param list Address of the linked list head to reorder in place.
 * @return This function does not return a value.
 */
void	sort_list(t_nodes **list)
{
	t_nodes	*cur;
	t_nodes	*next;

	cur = *list;
	while (cur)
	{
		next = cur->next;
		while (next)
		{
			if (should_swap_nodes(cur, next))
				swap_node_contents(cur, next);
			next = next->next;
		}
		cur = cur->next;
	}
}
