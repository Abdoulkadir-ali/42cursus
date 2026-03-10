/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 20:34:15 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 22:14:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_duplicates(t_nodes *stack)
{
	t_nodes	*outer;
	t_nodes	*inner;
	int		size;
	int		remaining;

	if (!stack)
		return (0);
	size = ft_size(stack);
	outer = stack;
	while (size--)
	{
		inner = outer->next;
		remaining = size;
		while (remaining--)
		{
			if (inner->v == outer->v)
				return (1);
			inner = inner->next;
		}
		outer = outer->next;
	}
	return (0);
}

int	is_duplicate(t_nodes *stack, int value)
{
	t_nodes	*curr;
	t_nodes	*start;

	if (!stack)
		return (0);
	curr = stack;
	start = stack;
	while (1)
	{
		if (curr->v == value)
			return (1);
		curr = curr->next;
		if (curr == start)
			break ;
	}
	return (0);
}

int	ft_isnum(char *str)
{
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!*str)
		return (0);
	while (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}
