/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 01:36:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:39:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Collect prefixes or return NULL when none expected.
 * @param tokens Token list for the command.
 * @param cmd Command meta describing expected prefix count.
 * @return Allocated prefix array or NULL when `prefix_count` is 0.
 */
static char	**collect_prefixes_or_null(t_nodes *tokens, t_cmd *cmd)
{
	char	**arr;

	if (cmd->prefix_count == 0)
		return (NULL);
	arr = collect_prefixes(tokens, cmd->prefix_count);
	if (!arr)
		ft_lstclear(&tokens, del_token);
	return (arr);
}

/**
 * @brief Build argv array or cleanup on failure.
 * @param tokens Token list for the command.
 * @param cmd Command meta with expected arg count.
 * @param prefix_arr Previously allocated prefix array to free on error.
 * @return Allocated argv array or NULL on failure.
 */
static char	**build_args_or_cleanup(t_nodes *tokens, t_cmd *cmd,
		char **prefix_arr)
{
	char	**args;

	args = build_args_from_tokens(tokens, cmd->count);
	if (!args)
	{
		free_string_array(prefix_arr);
		ft_lstclear(&tokens, del_token);
	}
	return (args);
}

/**
 * @brief Create and finalize a command AST node with redirections.
 * @param args argv array for the command.
 * @param prefix_arr Array of assignment prefixes, may be NULL.
 * @param tokens Token list scanned for redirections.
 * @param is_quoted Quote flag propagated to the AST node.
 * @return Finalized AST node or NULL on failure.
 */
static t_ast	*finalize_command_node(char **args, char **prefix_arr,
		t_nodes *tokens, bool is_quoted)
{
	t_ast	*node;

	node = create_node(TOKEN_WORD, args, NULL, NULL);
	if (!node)
	{
		free_string_array(args);
		free_string_array(prefix_arr);
		ft_lstclear(&tokens, del_token);
		return (NULL);
	}
	if (prefix_arr)
		node->assigns = prefix_arr;
	node = process_redirections(node, tokens);
	if (node)
		node->is_quoted = is_quoted;
	return (node);
}

/**
 * @brief Handle a command with no words, only possible redirections.
 * @param tokens Token list possibly containing redirections.
 * @return AST node representing the redirections, or NULL.
 */
static t_ast	*handle_empty_cmd(t_nodes *tokens)
{
	t_ast	*node;

	node = process_redirections(NULL, tokens);
	ft_lstclear(&tokens, del_token);
	return (node);
}

/**
 * @brief Build an AST node for a simple (non-subshell) command.
 * @param tokens Token list describing the command and its redirections.
 * @return Constructed AST node, or NULL on error.
 */
t_ast	*handle_simple_cmd(t_nodes *tokens)
{
	t_cmd	cmd;
	t_ast	*node;
	bool	is_quoted;

	scan_command_tokens(tokens, &cmd, &is_quoted);
	cmd.prefix_arr = collect_prefixes_or_null(tokens, &cmd);
	if (cmd.prefix_count > 0 && !cmd.prefix_arr)
		return (NULL);
	if (cmd.count == 0)
		return (handle_empty_cmd(tokens));
	cmd.args = build_args_or_cleanup(tokens, &cmd, cmd.prefix_arr);
	if (!cmd.args)
		return (NULL);
	node = finalize_command_node(cmd.args, cmd.prefix_arr, tokens, is_quoted);
	ft_lstclear(&tokens, del_token);
	return (node);
}
