/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:34:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static long long	parse_exit_argument(const char *arg)
{
	int			error;
	char		*endptr;
	long long	val;

	val = ft_safe_atoll(arg, LLONG_MAX, &error, &endptr);
	if (error)
	{
		ft_puterror("exit: %s: numeric argument required\n", arg);
		exit(2);
	}
	while (*endptr)
	{
		if (!(*endptr == ' ' || (*endptr >= 9 && *endptr <= 13)))
		{
			ft_puterror("exit: %s: numeric argument required\n", arg);
			exit(2);
		}
		endptr++;
	}
	return (val);
}

static int	get_exit_status(char **args, long long *status, t_shell_state *state)
{
	if (!args[1])
	{
		*status = state->exit_code;
		return (0);
	}
	*status = parse_exit_argument(args[1]);
	if (args[2])
	{
		ft_puterror("exit: too many arguments\n");
		*status = 1;
		return (0);
	}
	return (0);
}

int	ft_exit(char **args, t_shell_state *state)
{
	long long	status;

	if (state->interactive_shell)
		ft_putendl_fd("exit", 2);
	get_exit_status(args, &status, state);
	exit((unsigned char)status);
	return ((unsigned char)status);
}
