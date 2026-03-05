/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:13:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	swap_contents(t_nodes *a, t_nodes *b)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

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
