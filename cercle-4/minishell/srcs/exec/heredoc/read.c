/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 14:00:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	read_heredoc_loop(char *delim, int fd, char **envp, int exit_code)
{
	char		*stop_str;
	int			quoted;
	t_heredoc	ctx;

	ctx.envp = envp;
	ctx.exit_code = exit_code;
	ctx.fd = fd;
	stop_str = prepare_stop_str(delim, &ctx);
	quoted = is_quoted_delim(delim);
	setup_signals(SIGNAL_HEREDOC);
	read_heredoc_lines(stop_str, quoted, &ctx);
	setup_signals(SIGNAL_INTERACTIVE);
	free(stop_str);
}

void	handle_heredoc_eof(char *stop_str)
{
	const char	*error;

	error = "warning: here-document delimited by end-of-file";
	if (stop_str && g_state.last_signal != 130)
		ft_puterror("%s (wanted `%s')\n", error, stop_str);
}

int	process_heredoc_line(char *line, char *stop_str, int quoted, t_heredoc *ctx)
{
	if (quoted)
		return (process_line_quoted(line, stop_str, ctx->fd));
	else
		return (process_line_unquoted(line, stop_str, ctx->fd, ctx));
}

void	read_heredoc_lines(char *stop_str, int quoted, t_heredoc *ctx)
{
	char	*line;

	while (1)
	{
		line = read_line();
		if (!line)
		{
			handle_heredoc_eof(stop_str);
			break ;
		}
		if (process_heredoc_line(line, stop_str, quoted, ctx))
		{
			free(line);
			break ;
		}
		free(line);
	}
}
