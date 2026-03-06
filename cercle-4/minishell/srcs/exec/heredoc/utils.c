/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 04:48:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:27:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*expand_delim(const char *delim, int quoted, t_shell_state *state)
{
	char	*expanded;

	if (quoted)
		return ((char *)delim);
	expanded = expand_heredoc((char *)delim, state->envp, state->exit_code);
	if (expanded)
		return (expanded);
	return ((char *)delim);
}

static int	has_double_quote(const char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (delim[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

char	*prepare_stop_str(char *delim, t_heredoc *ctx)
{
	int		quoted;
	char	*stop_str;
	char	*expanded;

	quoted = is_quoted_delim(delim);
	if (quoted)
	{
		stop_str = remove_quotes_heredoc(delim);
		if (has_double_quote(delim) && stop_str)
		{
			expanded = expand_string(stop_str, ctx->state->envp,
					ctx->state->exit_code);
			free(stop_str);
			stop_str = expanded;
		}
	}
	else
		stop_str = expand_string(delim, ctx->state->envp,
				ctx->state->exit_code);
	if (!stop_str)
		stop_str = ft_strdup(delim);
	return (stop_str);
}

char	*heredoc_read_line_non_tty(void)
{
	char	*line;
	size_t	len;

	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

char	*heredoc_read_line(void)
{
	if (isatty(STDIN_FILENO))
		return (readline("> "));
	else
		return (heredoc_read_line_non_tty());
}
