/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 04:47:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include <errno.h>
#include <stdlib.h>

static int	check_long_overflow(const char *str)
{
	char *endptr;
	long long val;

	errno = 0;
	val = strtoll(str, &endptr, 10);
	if (errno == ERANGE)
		return (0);
	/* skip leading whitespace - strtoll does this, but ensure we consumed
	   at least one digit or sign and that there are no trailing garbage
	   characters (only spaces allowed). */
	if (endptr == str)
		return (0);
	while (*endptr)
	{
		if (!(*endptr == ' ' || (*endptr >= 9 && *endptr <= 13)))
			return (0);
		endptr++;
	}
	(void)val;
	return (1);
}

static int	get_exit_status(char **args, long long *status)
{
	if (!args[1])
	{
		*status = g_state.exit_code;
		return (0);
	}
	if (!check_long_overflow(args[1]))
	{
		ft_puterror("exit: %s: numeric argument required\n", args[1]);
		exit(2);
	}
	*status = ft_atoll(args[1]);
	if (args[2])
	{
		ft_puterror("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	ft_exit(char **args)
{
	long long	status;

	if (g_state.interactive_shell)
		ft_putendl_fd("exit", 2);
	if (get_exit_status(args, &status))
		return (1);
	exit((unsigned char)status);
	return ((unsigned char)status);
}
