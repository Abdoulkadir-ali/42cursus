/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 01:26:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_long_overflow(const char *str)
{
	unsigned long long	res;
	int					sign;
	int					i;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
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
		if (!ft_isdigit(str[i]))
			return (0);
		if (res > LLONG_MAX || (res == LLONG_MAX && (str[i] - '0') > (7
					+ (sign == -1))))
			return (0);
		res = res * 10 + (str[i++] - '0');
	}
	return (1);
}

int	ft_exit(char **args)
{
	long long	status;

	if (g_interactive_shell)
		ft_putendl_fd("exit", 2);
	if (args[1])
	{
		if (!check_long_overflow(args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		status = ft_atoll(args[1]);
		if (args[2])
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			return (1);
		}
	}
	else
		status = g_exit_code;
	exit((unsigned char)status);
	return ((unsigned char)status);
}
