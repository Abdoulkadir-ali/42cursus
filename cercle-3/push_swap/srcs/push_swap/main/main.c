/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:45:56 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/12 23:12:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	char		**args;

	stacks = (t_stacks){NULL, NULL, 0};
	if (argc < 2)
		return (ft_puterr("Error\n"));
	argv++;
	if (argc == 2)
	{
		args = ft_split(*argv, ' ');
		if (!args)
			return (ft_puterr("Error\n"));
		init_stacks(&stacks, args);
		ft_free_split(args);
	}
	else
		init_stacks(&stacks, argv);
	if (!stacks.a)
		return (ft_puterr("Error\n"));
	if (DEBUG)
	{
		ft_putstr_fd("Before :\n", 1);
		debug_stacks(stacks);
	}
	push_swap(&stacks);
	if (DEBUG)
	{
		ft_putstr_fd("After :\n", 1);
		debug_stacks(stacks);
	}
	free_stacks(stacks);
	return (0);
}
