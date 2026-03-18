/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:39 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:16:40 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Resolve the effective heredoc delimiter and quoted flag.
 * @param args Heredoc argument vector containing delimiter metadata.
 * @param quoted Output flag indicating whether the delimiter is quoted.
 * @return Delimiter string to use for heredoc reading.
 */
static char	*get_heredoc_delim(char **args, int *quoted, t_shell_state *state)
{
	char	*delim;

	delim = args[0];
	*quoted = 0;
	if (args[1])
		*quoted = ft_atoi(args[1]);
	if (!(*quoted))
	{
		delim = expand_delim(args[0], state);
		return (delim);
	}
	return (delim);
}

/**
 * @brief Write heredoc input into a temporary file and return its path.
 * @param delim Effective heredoc delimiter.
 * @param state Active shell state passed to the read loop.
 * @param quoted Non-zero when the delimiter disables expansion.
 * @return Newly allocated temporary filename, or NULL on failure.
 */
static char	*write_heredoc_to_file(char *delim, t_shell_state *state,
		int quoted, char **args)
{
	char	*filename;
	int		fd;

	filename = generate_tmp_filename(&fd);
	if (fd == -1)
	{
		perror("heredoc tmp");
		free(filename);
		if (!quoted && delim != args[0])
			free(delim);
		return (NULL);
	}
	read_heredoc_loop(delim, fd, state, quoted);
	close(fd);
	return (filename);
}

/**
 * @brief Collect heredoc input for one AST heredoc node.
 * @param args Heredoc argument vector containing the delimiter and flags.
 * @param state Active shell state passed to heredoc helpers.
 * @return Temporary filename containing the heredoc body, or NULL.
 */
char	*handle_heredoc_input(char **args, t_shell_state *state)
{
	int		quoted;
	char	*delim;
	char	*filename;

	delim = get_heredoc_delim(args, &quoted, state);
	filename = write_heredoc_to_file(delim, state, quoted, args);
	if (!filename)
	{
		if (!quoted && delim != args[0])
			free(delim);
		return (NULL);
	}
	if (!quoted && delim != args[0])
		free(delim);
	if (g_last_signal == 130)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}
