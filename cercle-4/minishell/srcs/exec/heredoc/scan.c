/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:25:16 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	create_tmp_file(int *fd, char **tmp_file)
{
	*tmp_file = generate_tmp_filename(fd);
	if (*fd == -1 || !*tmp_file)
	{
		free(*tmp_file);
		return (1);
	}
	return (0);
}

static char	*expand_here_word(char *word, t_shell_state *state, int quoted)
{
	char	*use_word;

	use_word = word;
	if (!quoted)
		return (expand_delim(word, quoted, state));
	return (use_word);
}

static void	write_here_word(int fd, char *use_word)
{
	write(fd, use_word, ft_strlen(use_word));
	write(fd, "\n", 1);
}

static int	handle_herestr(t_ast *node, t_shell_state *state)
{
	char	*tmp_file;
	int		fd;
	char	*word;
	int		quoted;
	char	*use_word;

	if (create_tmp_file(&fd, &tmp_file))
		return (1);
	if (node->args && node->args[0])
	{
		word = node->args[0];
		quoted = 0;
		if (node->args[1])
			quoted = ft_atoi(node->args[1]);
		use_word = expand_here_word(word, state, quoted);
		write_here_word(fd, use_word);
		if (!quoted && use_word != word)
			free(use_word);
	}
	close(fd);
	free(node->args[0]);
	node->args[0] = tmp_file;
	node->type = TOKEN_RED_IN;
	return (0);
}

int	scan_heredocs(t_ast *ast_node, t_shell_state *state)
{
	char	*tmp_file;

	if (!ast_node)
		return (0);
	if (ast_node->type == TOKEN_HEREDOC)
	{
		tmp_file = handle_heredoc_input(ast_node->args, state);
		if (!tmp_file)
			return (1);
		free(ast_node->args[0]);
		ast_node->args[0] = tmp_file;
		ast_node->type = TOKEN_RED_IN;
	}
	else if (ast_node->type == TOKEN_HERESTR)
		return (handle_herestr(ast_node, state));
	if (scan_heredocs(ast_node->left, state)
		|| scan_heredocs(ast_node->right, state))
		return (1);
	return (0);
}
