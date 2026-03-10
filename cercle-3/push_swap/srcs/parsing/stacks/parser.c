/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:52:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/16 17:14:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	add_numbers_from_split(t_stacks *stacks, char **split)
{
	int		i;
	long	val;
	int		error;
	t_nodes	*new_a;

	i = 0;
	while (split[i])
	{
		if (*split[i] == '\0')
		{
			i++;
			continue ;
		}
		val = parse_int(split[i], &error);
		if (error)
			return (-1);
		if (is_duplicate(stacks->a, (int)val))
			return (-1);
		new_a = ft_new((int)val);
		if (!new_a)
			return (-1);
		ft_add_back(&stacks->a, new_a);
		i++;
	}
	return (0);
}

static int	process_string(t_stacks *stacks, char *str)
{
	char	**split;
	int		result;

	split = ft_split(str, ' ');
	if (!split)
		return (-1);
	result = add_numbers_from_split(stacks, split);
	ft_free_split(split);
	return (result);
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
