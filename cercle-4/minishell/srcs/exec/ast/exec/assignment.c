/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 03:04:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 05:22:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Restores the original environment and frees the duplicated one.
 * @param state Shell state whose `envp` will be restored.
 * @param saved_env The original envp that was saved.
 * @return This function does not return a value.
 */
void	restore_env_and_free(t_shell_state *state, char **saved_env)
{
	if (saved_env)
	{
		free_string_array(state->envp);
		state->envp = saved_env;
	}
}

/**
 * @brief Apply assignment prefixes from an AST node into the provided env.
 * @param node AST node containing `assigns` array.
 * @param state Shell state whose `envp` will be updated.
 * @return This function does not return a value.
 */
void	apply_assigns_to_state(t_ast *node, t_shell_state *state)
{
	size_t	i;
	char	*eq;
	char	*key;
	char	*val;

	if (!node || !node->assigns)
		return ;
	i = 0;
	while (node->assigns[i])
	{
		eq = ft_strchr(node->assigns[i], '=');
		if (eq)
		{
			key = ft_strldup(node->assigns[i], (size_t)(eq - node->assigns[i]));
			val = ft_strdup(eq + 1);
			ft_set_env(key, val, state);
			free(key);
			free(val);
		}
		i++;
	}
}

/**
 * @brief Saves the current environment, duplicates it, and applies assignments.
 * @param node AST node containing `assigns` array.
 * @param state Shell state whose `envp` will be updated.
 * @param saved_env Pointer to a char*** to store the original envp.
 * @return 0 on success, 1 on failure (e.g., memory allocation error).
 */
int	save_and_apply_assigns(t_ast *node, t_shell_state *state, char ***saved_env)
{
	*saved_env = NULL;
	if (!node->assigns || !node->assigns[0])
		return (0);
	*saved_env = state->envp;
	state->envp = duplicate_envp(*saved_env);
	if (!state->envp)
	{
		state->envp = *saved_env;
		*saved_env = NULL;
		return (1);
	}
	apply_assigns_to_state(node, state);
	return (0);
}
