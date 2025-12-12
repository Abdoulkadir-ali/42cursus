/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 16:52:22 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 22:43:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	parse_number(char **p, int *value)
{
	char	*start;
	char	temp;
	int		error;
	long	val;

	while (is_space(**p))
		(*p)++;
	if (!**p)
		return (0);
	start = *p;
	if (**p == '+' || **p == '-')
		(*p)++;
	if (!ft_isdigit(**p))
		return (-1);
	while (ft_isdigit(**p))
		(*p)++;
	if (**p && !is_space(**p))
		return (-1);
	temp = **p;
	**p = '\0';
	val = parse_int(start, &error);
	**p = temp;
	if (error)
		return (-1);
	*value = (int)val;
	return (1);
}

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
