/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 22:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:26:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	process_line_quoted(char *line, char *stop_str, int fd)
{
	char	*trimmed_line;
	size_t	len;

	trimmed_line = ft_strtrim(line, " \t");
	len = ft_strlen(stop_str) + 1;
	if (ft_strncmp(trimmed_line, stop_str, len) == 0)
	{
		free(trimmed_line);
		return (1);
	}
	ft_putendl_fd(line, fd);
	free(trimmed_line);
	return (0);
}

int	process_line_unquoted(char *line, char *stop_str, int fd, t_heredoc *ctx)
{
	char	*expanded_candidate;
	char	*trimmed_expanded;
	size_t	len;

	expanded_candidate = expand_heredoc(line, ctx->state->envp,
			ctx->state->exit_code);
	trimmed_expanded = ft_strtrim(expanded_candidate, " \t");
	len = ft_strlen(stop_str) + 1;
	if (ft_strncmp(trimmed_expanded, stop_str, len) == 0)
	{
		free(expanded_candidate);
		free(trimmed_expanded);
		return (1);
	}
	ft_putendl_fd(expanded_candidate, fd);
	free(expanded_candidate);
	free(trimmed_expanded);
	return (0);
}
