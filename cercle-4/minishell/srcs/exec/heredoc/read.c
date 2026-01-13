/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 23:45:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	read_heredoc_loop(char *delim, int fd, char **envp, int exit_code)
{
	char					*stop_str;
	int						quoted;
	struct s_heredoc_ctx	ctx;

	ctx.envp = envp;
	ctx.exit_code = exit_code;
	stop_str = prepare_stop_str(delim, &ctx);
	quoted = is_quoted_delim(delim);
	setup_signals(SIGNAL_HEREDOC);
	read_heredoc_lines(stop_str, quoted, fd, &ctx);
	setup_signals(SIGNAL_INTERACTIVE);
	free(stop_str);
}

void	handle_heredoc_eof(char *stop_str)
{
	if (g_last_signal != 130)
	{
		ft_putstr_fd("minishell: warning: here-document delimited by end-of-file ",
			2);
		ft_putstr_fd("(wanted `", 2);
		ft_putstr_fd(stop_str, 2);
		ft_putendl_fd("')", 2);
	}
}

int	process_heredoc_line(char *line, char *stop_str, int quoted, int fd,
		struct s_heredoc_ctx *ctx)
{
	if (quoted)
		return (process_line_quoted(line, stop_str, fd));
	else
		return (process_line_unquoted(line, stop_str, fd, ctx));
}

void	read_heredoc_lines(char *stop_str, int quoted, int fd,
		struct s_heredoc_ctx *ctx)
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
		if (process_heredoc_line(line, stop_str, quoted, fd, ctx))
		{
			free(line);
			break ;
		}
		free(line);
	}
}
