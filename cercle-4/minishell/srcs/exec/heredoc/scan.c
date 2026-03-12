/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:26:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Create the temporary file backing a here-string or heredoc node.
 * @param fd Output slot receiving the opened descriptor.
 * @param tmp_file Output slot receiving the temporary filename.
 * @return 0 on success, 1 on failure.
 */
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

/**
 * @brief Resolve the text that must be written for a here-string node.
 * @param node AST node holding the here-string arguments.
 * @param quoted Output flag indicating whether expansion is disabled.
 * @return String to write into the temporary input file.
 */
static char	*get_herestr_word(t_ast *node, int *quoted)
{
	char	*word;

	if (!node->args || !node->args[0])
		return (NULL);
	word = node->args[0];
	*quoted = 0;
	if (node->args[1])
		*quoted = ft_atoi(node->args[1]);
	if (!*quoted)
		return (expand_delim(word));
	return (word);
}

/**
 * @brief Write one here-string payload into its temporary file.
 * @param node AST node holding the here-string arguments.
 * @param state Active shell state used for optional expansion.
 * @param fd Temporary file descriptor receiving the data.
 * @return This function does not return a value.
 */
static void	write_herestr(t_ast *node, int fd)
{
	char	*use_word;
	int		quoted;

	use_word = get_herestr_word(node, &quoted);
	if (!use_word)
		return ;
	write(fd, use_word, ft_strlen(use_word));
	write(fd, "\n", 1);
	if (!quoted && use_word != node->args[0])
		free(use_word);
}

/**
 * @brief Convert a here-string node into a regular input redirection node.
 * @param node AST node that currently represents a here-string.
 * @return 0 on success, 1 on failure.
 */
static int	handle_herestr(t_ast *node)
{
	char	*tmp_file;
	int		fd;

	if (create_tmp_file(&fd, &tmp_file))
		return (1);
	write_herestr(node, fd);
	close(fd);
	free(node->args[0]);
	node->args[0] = tmp_file;
	if (node->args[1])
		free(node->args[1]);
	node->args[1] = NULL;
	node->type = TOKEN_RED_IN;
	return (0);
}

/**
 * @brief Scan the AST and materialize heredocs before execution starts.
 * @param ast_node Current AST node visited during the recursive scan.
 * @param state Active shell state passed to heredoc helpers.
 * @return 0 on success, 1 when one heredoc preparation fails.
 */
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
		if (ast_node->args[1])
			free(ast_node->args[1]);
		ast_node->args[1] = NULL;
		ast_node->type = TOKEN_RED_IN;
	}
	else if (ast_node->type == TOKEN_HERESTR)
		return (handle_herestr(ast_node));
	if (scan_heredocs(ast_node->left, state)
		|| scan_heredocs(ast_node->right, state))
		return (1);
	return (0);
}
