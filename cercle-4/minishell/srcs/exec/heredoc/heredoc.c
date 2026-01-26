/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:36:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	handle_herestr(t_ast *node)
{
	char	*tmp_file;
	int		fd;

	tmp_file = generate_tmp_filename();
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		free(tmp_file);
		return (1);
	}
	if (node->args && node->args[0])
	{
		write(fd, node->args[0], ft_strlen(node->args[0]));
		write(fd, "\n", 1);
	}
	close(fd);
	free(node->args[0]);
	node->args[0] = tmp_file;
	node->type = TOKEN_RED_IN;
	return (0);
}

int	scan_heredocs(t_nodes *ast_node, t_shell_state *state)
{
	t_ast	*node;
	char	*tmp_file;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_HEREDOC)
	{
		tmp_file = handle_heredoc_input(node->args[0], state);
		if (!tmp_file)
			return (1);
		free(node->args[0]);
		node->args[0] = tmp_file;
		node->type = TOKEN_RED_IN;
	}
	else if (node->type == TOKEN_HERESTR)
		return (handle_herestr(node));
	if (scan_heredocs(node->left, state) || scan_heredocs(node->right, state))
		return (1);
	return (0);
}
