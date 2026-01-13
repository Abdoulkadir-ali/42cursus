/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:06:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	scan_heredocs(t_nodes *ast_node)
{
	t_ast	*node;
	char	*tmp_file;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_HEREDOC)
	{
		tmp_file = handle_heredoc_input(node->args[0], g_envp, g_exit_code);
		if (!tmp_file)
			return (1);
		free(node->args[0]);
		node->args[0] = tmp_file;
		node->type = TOKEN_RED_IN;
	}
	if (scan_heredocs(node->left) || scan_heredocs(node->right))
		return (1);
	return (0);
}

void consume_heredocs(t_nodes *tokens)
{
	t_token	*tok;
	t_token	*next_tok;
	char 	*filename;
	int		fd;

	while (tokens)
	{
		tok = (t_token *)tokens->content;
		if (tok->type == TOKEN_HEREDOC)
		{
			if (tokens->next)
			{
				next_tok = (t_token *)tokens->next->content;
				if (next_tok->type == TOKEN_WORD)
				{
					filename = generate_tmp_filename();
					fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if (fd != -1)
					{
						read_heredoc_loop(next_tok->value, fd, g_envp, g_exit_code);
						close(fd);
						unlink(filename);
					}
					free(filename);
				}
			}
		}
		tokens = tokens->next;
	}
}

