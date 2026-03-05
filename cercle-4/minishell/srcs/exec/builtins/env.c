/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:06:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_env(char **args, t_shell_state *state)
{
	int	i;

	(void)args;
	i = 0;
	while (state->envp && state->envp[i])
	{
		if (ft_strchr(state->envp[i], '='))
			ft_putendl_fd(state->envp[i], 1);
		i++;
	}
	return (0);
}
