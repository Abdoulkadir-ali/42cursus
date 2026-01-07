/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 19:45:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/06 17:36:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	char		**args;


	stacks = (t_stacks){NULL, NULL, 0};
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
	debug_line_stacks(stacks, "Before state:", NULL);
	push_swap(&stacks);
	debug_line_stacks(stacks, "After state:", NULL);
	free_stacks(stacks);
	return (0);
}
