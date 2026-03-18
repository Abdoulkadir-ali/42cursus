/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:58 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:59 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Parse repeated `-n` options accepted by echo.
 * @param args Argument vector passed to the builtin.
 * @param newline Output flag cleared when `-n` is present.
 * @return Index of the first non-option argument.
 */
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

/**
 * @brief Print echo arguments separated by a single space.
 * @param args Argument vector passed to the builtin.
 * @param start Index of the first argument that must be printed.
 * @return This function does not return a value.
 */
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

/**
 * @brief Execute the echo builtin with support for repeated `-n` flags.
 * @param args Argument vector for the echo command.
 * @param state Unused shell state.
 * @return Always returns 0.
 */
int	ft_echo(char **args, t_shell_state *state)
{
	int	newline;
	int	start;

	(void)state;
	start = parse_echo_options(args, &newline);
	print_echo_args(args, start);
	if (newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
