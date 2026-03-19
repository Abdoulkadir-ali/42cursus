/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 03:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:21:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Internal helper to expand a token list 
 * and convert it to a string array.
 * @param list Linked list of tokens to expand.
 * @param state Active shell state used for environment resolution.
 * @return Null-terminated array of expanded strings.
 */
static char	**expand_tokens_to_array(t_nodes *list, t_shell_state *state)
{
	char	**res;

	expand_tokens(&list, state->envp, state->exit_code);
	res = token_list_to_array(list);
	ft_lstclear(&list, del_token);
	return (res);
}

/**
 * @brief Expand and split an array of strings using shell expansion rules.
 * @param arr Input array of raw command or assignment tokens.
 * @param state Active shell state.
 * @return Null-terminated array containing expanded and split tokens.
 */
char	**expand_string_array(char **arr, t_shell_state *state)
{
	t_nodes	*list;
	t_nodes	*tail;
	int		i;

	if (!arr)
		return (NULL);
	list = NULL;
	tail = NULL;
	i = 0;
	while (arr[i])
	{
		add_token_node(&list, &tail, ft_strdup(arr[i]), 0);
		if (tail)
			((t_token *)tail->content)->type = TOKEN_WORD;
		i++;
	}
	return (expand_tokens_to_array(list, state));
}

/**
 * @brief Expand a single filename for redirection purpose.
 * @param filename Raw filename string (e.g. from the AST).
 * @param state Active shell state.
 * @return Array of matches (must be exactly 1 for non-ambiguous redirection).
 */
char	**expand_redirection_filename(char *filename, t_shell_state *state)
{
	t_nodes	*list;
	t_nodes	*tail;

	if (!filename)
		return (NULL);
	list = NULL;
	tail = NULL;
	add_token_node(&list, &tail, ft_strdup(filename), 0);
	if (!tail)
		return (NULL);
	((t_token *)tail->content)->type = TOKEN_WORD;
	return (expand_tokens_to_array(list, state));
}
