/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:40:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:28:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static char	**duplicate_env_base(char **envp)
{
	int		env_count;
	char	**heap_env;
	int		i;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	heap_env = malloc(sizeof(char *) * (env_count + 2));
	if (!heap_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		heap_env[i] = ft_strdup(envp[i]);
		i++;
	}
	heap_env[i] = NULL;
	return (heap_env);
}

int	init_shell(char **envp, char ***heap_env, t_shell_state *state)
{
	*heap_env = duplicate_env_base(envp);
	if (!*heap_env)
		return (1);
	add_shlvl_to_env(*heap_env);
	state->envp = *heap_env;
	state->interactive_shell = isatty(STDIN_FILENO);
	state->exit_code = 0;
	state->syntax_error = 0;
	state->expansion_error = 0;
	return (0);
}
