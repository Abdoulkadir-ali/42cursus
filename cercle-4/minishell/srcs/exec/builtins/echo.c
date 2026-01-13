/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:13:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	parse_echo_options(char **args, int *newline)
{
	int	i;
	int	j;

	*newline = 1;
	i = 1;
	while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			*newline = 0;
			i++;
		}
		else
			break ;
	}
	return (i);
}

static void	print_echo_args(char **args, int start)
{
	while (args[start])
	{
		ft_putstr_fd(args[start], 1);
		if (args[start + 1])
			ft_putchar_fd(' ', 1);
		start++;
	}
}

int	ft_echo(char **args)
{
	int	newline;
	int	start;

	start = parse_echo_options(args, &newline);
	print_echo_args(args, start);
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
