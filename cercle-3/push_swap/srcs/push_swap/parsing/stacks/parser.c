/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:52:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/13 00:33:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	process_string(t_stacks *stacks, char *str)
{
	char	*p;
	int		val;
	int		ret;
	t_nodes	*new_a;

	p = str;
	while (*p)
	{
		ret = parse_number(&p, &val);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			break ;
		if (is_duplicate(stacks->a, val))
			return (-1);
		new_a = ft_new(val);
		if (!new_a)
			return (-1);
		ft_add_back(&stacks->a, new_a);
	}
	return (0);
}

void	init_stacks(t_stacks *stacks, char **strs)
{
	stacks->a = NULL;
	stacks->b = NULL;
	stacks->verbose = 1;
	while (*strs)
	{
		if (process_string(stacks, *strs) == -1)
		{
			ft_clear(&stacks->a);
			stacks->a = NULL;
			return ;
		}
		strs++;
	}
}
