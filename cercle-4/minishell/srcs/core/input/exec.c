/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:51:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 03:07:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

int	check_if_assignment_candidate(t_nodes *segment, t_token **first_tok,
		char **eq)
{
	*first_tok = (t_token *)segment->content;
	if (!*first_tok || (*first_tok)->type != TOKEN_WORD)
		return (0);
	*eq = ft_strchr((*first_tok)->value, '=');
	if (!*eq || *eq == (*first_tok)->value)
		return (0);
	return (1);
}

int	validate_identifier(char *k)
{
	char	*p;

	if (!ft_isalpha((unsigned char)k[0]) && k[0] != '_')
		return (0);
	p = k;
	while (*p && *p != '=')
	{
		if (!ft_isalnum((unsigned char)*p) && *p != '_')
			return (0);
		p++;
	}
	return (1);
}

void	perform_assignment(t_token *first_tok, char *eq, char ***envp,
		int *exit_code)
{
	char	*key;
	char	*val;

	key = ft_substr(first_tok->value, 0, eq - first_tok->value);
	val = ft_strdup(eq + 1);
	ft_set_env(key, val, envp);
	free(key);
	free(val);
	*exit_code = 0;
}

int	process_segment_local(t_nodes *segment, char ***envp, int *exit_code)
{
	expand_tokens(&segment, *envp, *exit_code);
	if (g_expansion_error)
	{
		*exit_code = g_exit_code;
		ft_lstclear(&segment, del_token);
		g_expansion_error = 0;
		return (1);
	}
	execute_command(segment, envp, exit_code);
	return (0);
}

void	execute_command(t_nodes *tokens, char ***envp, int *exit_code)
{
	t_nodes	*ast;

	ast = ast_builder(tokens);
	if (!scan_heredocs(ast))
		*exit_code = exec_tree(ast, envp);
	else
	{
		if (g_last_signal == 130)
			*exit_code = 130;
		else
			*exit_code = 1;
	}
	free_ast(ast);
}
