/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 10:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:15:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	consume_heredocs(t_nodes *tokens, t_shell_state *state)
{
	while (tokens)
	{
		process_heredoc(tokens, state);
		tokens = tokens->next;
	}
}

static char	*get_heredoc_delim(char **args, t_shell_state *state, int *quoted)
{
	char	*delim;
	char	*expanded;

	delim = args[0];
	*quoted = 0;
	if (args[1])
		*quoted = ft_atoi(args[1]);
	if (!(*quoted))
	{
		expanded = expand_heredoc(delim, state->envp, state->exit_code);
		if (expanded)
			return (expanded);
	}
	return (delim);
}

static char	*write_heredoc_to_file(char *delim, t_shell_state *state,
		int quoted)
{
	char	*filename;
	int		fd;

	filename = generate_tmp_filename(&fd);
	if (fd == -1)
	{
		perror("heredoc tmp");
		free(filename);
		if (!quoted && delim != state->envp[0])
			free(delim);
		return (NULL);
	}
	read_heredoc_loop(delim, fd, state);
	close(fd);
	return (filename);
}

char	*handle_heredoc_input(char **args, t_shell_state *state)
{
	int		quoted;
	char	*delim;
	char	*filename;

	delim = get_heredoc_delim(args, state, &quoted);
	filename = write_heredoc_to_file(delim, state, quoted);
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
