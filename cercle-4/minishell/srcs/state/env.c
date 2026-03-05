/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:06:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

static char	**duplicate_env_base(char **envp)
{
	int		env_count;
	char	**heap_env;
	int		i;

	env_count = 0;
	while (envp && envp[env_count])
		env_count++;
	heap_env = ft_calloc(env_count + 2, sizeof(char *));
	if (!heap_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		heap_env[i] = ft_strdup(envp[i]);
		if (!heap_env[i])
		{
			while (--i >= 0)
				free(heap_env[i]);
			free(heap_env);
			return (NULL);
		}
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

char	*ft_get_env(const char *key, char **envp)
{
	int		i;
	size_t	len;

	if (!key || !envp)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}
