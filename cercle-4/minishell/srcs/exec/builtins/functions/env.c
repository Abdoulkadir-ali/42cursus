/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Print exported environment entries that contain an equals sign.
 * @param args Unused builtin argument vector.
 * @param state Shell state providing the current environment.
 * @return Always returns 0.
 */
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
