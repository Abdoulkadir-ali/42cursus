/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 05:01:13 by abdoali          ###   ########.fr       */
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
	int		attempts;

	attempts = 0;
	i = *list;
	while (i && attempts++ < 10000)
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
