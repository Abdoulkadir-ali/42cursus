/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:17:03 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/25 12:41:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

/**
 * @brief Duplicate the inherited environment into heap-owned storage.
 * @param envp Environment array inherited from the parent process.
 * @return Newly allocated environment copy, or NULL on allocation failure.
 */
static char	**duplicate_env_base(char **envp)
{
	size_t	env_count;
	char	**heap_env;
	size_t	i;

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
			while (i > 0)
				free(heap_env[--i]);
			free(heap_env);
			return (NULL);
		}
		i++;
	}
	heap_env[i] = NULL;
	return (heap_env);
}

/**
 * @brief Public wrapper returning a duplicated environment array.
 * @param envp Source environment array.
 * @return Newly allocated copy of envp, or NULL on allocation failure.
 */
char	**duplicate_envp(char **envp)
{
	return (duplicate_env_base(envp));
}

/**
 * @brief Initialize shell state and its owned environment copy.
 * @param envp Environment array inherited from the parent process.
 * @param state Shell state structure initialized by this function.
 * @return 0 on success, 1 on allocation failure.
 */
bool	init_shell(char **envp, t_shell_state *state)
{
	state->envp = duplicate_env_base(envp);
	if (!state->envp)
		return (false);
	add_shlvl_to_env(state->envp);
	rl_outstream = stderr;
	state->interactive_shell = false;
	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		state->interactive_shell = true;
	state->exit_code = 0;
	state->syntax_error = false;
	state->expansion_error = false;
	return (true);
}

/**
 * @brief Look up one environment variable value by key.
 * @param key Environment variable name without the trailing `=`.
 * @param envp Environment array to search.
 * @return Pointer to the value substring, or NULL when not found.
 */
char	*ft_get_env(const char *key, char **envp)
{
	size_t	i;
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
