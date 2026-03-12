/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:15:13 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:40:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/**
 * @brief Append a continued line after removing the active trailing backslash.
 * @param line Current accumulated input line.
 * @param new_line Fresh continuation line.
 * @param i Index of the trailing backslash to remove.
 * @return Newly allocated concatenated line.
 */
static char	*append_with_backslash(char *line, char *new_line, size_t i)
{
	char	*result;

	line[i] = '\0';
	result = ft_strjoin(line, new_line);
	return (result);
}

/**
 * @brief Append a continued line by inserting a literal newline first.
 * @param line Current accumulated input line.
 * @param new_line Fresh continuation line.
 * @return Newly allocated concatenated line, or NULL on allocation failure.
 */
static char	*append_with_newline(char *line, char *new_line)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(line, "\n");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, new_line);
	free(temp);
	return (result);
}

/**
 * @brief Merge one continuation line into the current accumulated input.
 * @param line Current accumulated input line.
 * @param new_line Fresh continuation line.
 * @param code Continuation code that triggered the extra read.
 * @return Newly allocated combined line, or NULL when inputs are missing.
 */
char	*append_line(char *line, char *new_line, char code)
{
	size_t	len;
	size_t	i;

	if (!line || !new_line)
		return (NULL);
	len = ft_strlen(line);
	if (len == 0)
		return (append_with_newline(line, new_line));
	i = len - 1;
	while (i > 0 && ft_isspace(line[i]))
		i--;
	if (code == '\\' && line[i] == '\\')
		return (append_with_backslash(line, new_line, i));
	else
		return (append_with_newline(line, new_line));
}

/**
 * @brief Return the prompt string used by the reader layer.
 * @param is_initial True for the main shell prompt, false for fallback use.
 * @return Prompt string, or NULL when stdin is not interactive.
 */
char	*get_prompt(bool is_initial)
{
	if (!isatty(STDIN_FILENO))
		return (NULL);
	if (is_initial)
		return ("minishell> ");
	return ("> ");
}
