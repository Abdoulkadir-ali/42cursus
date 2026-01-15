/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 01:54:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_long_overflow(const char *str)
{
	size_t	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]) || (res > LLONG_MAX) || (res == LLONG_MAX
				&& (str[i] - '0') > (7 + (sign == -1))))
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
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
