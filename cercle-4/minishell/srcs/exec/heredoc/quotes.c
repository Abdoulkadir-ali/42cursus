/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:43 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/19 07:23:10 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Generate a unique temporary filename 
 * for a heredoc and open it.
 * @param fd_out Pointer to an int where the opened
 * file descriptor will be stored.
 * @return Allocated filename string on success
 * (caller must free), or NULL on failure.
 */
char	*generate_tmp_filename(int *fd_out)
{
	char		*filename;
	char		*pid_str;
	static int	counter = 0;
	char		*counter_str;
	char		*tmp;

	pid_str = ft_itoa(getpid());
	while (counter < 1000000)
	{
		counter_str = ft_itoa(counter++);
		tmp = ft_strjoin("/tmp/.minishell_heredoc_", pid_str);
		filename = ft_strjoin(tmp, counter_str);
		free(tmp);
		free(counter_str);
		*fd_out = open(filename, O_RDWR | O_CREAT | O_EXCL, 0600);
		if (*fd_out != -1)
		{
			free(pid_str);
			return (filename);
		}
		free(filename);
	}
	free(pid_str);
	return (NULL);
}

/**
 * @brief Check whether a heredoc delimiter contains quote semantics.
 * @param delim Raw delimiter string.
 * @return True when the delimiter contains quotes or escapes, else false.
 */
bool	is_quoted_delim(const char *delim)
{
	size_t	i;

	if (!delim)
		return (false);
	i = 0;
	while (delim[i])
	{
		if (delim[i] == '\'' || delim[i] == '"' || delim[i] == '\\')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Copy one quoted section while stripping the surrounding quote pair.
 * @param str Source delimiter string.
 * @param res Destination buffer receiving the unquoted characters.
 * @param state Quote-removal cursor state updated in place.
 * @return This function does not return a value.
 */
static void	handle_inside_quote(const char *str, char *res,
		t_quotes_state *state)
{
	if (str[state->i] == state->quote)
	{
		state->quote = 0;
		state->i++;
	}
	else
	{
		res[state->j++] = str[state->i++];
	}
}

/**
 * @brief Process one unquoted delimiter character during quote removal.
 * @param str Source delimiter string.
 * @param res Destination buffer receiving the unquoted characters.
 * @param state Quote-removal cursor state updated in place.
 * @return This function does not return a value.
 */
static void	handle_outside_quote(const char *str, char *res,
		t_quotes_state *state)
{
	if (str[state->i] == '\\')
	{
		state->i++;
		if (str[state->i])
			res[state->j++] = str[state->i++];
	}
	else if (str[state->i] == '\'' || str[state->i] == '"')
		state->quote = str[state->i++];
	else
		res[state->j++] = str[state->i++];
}

/**
 * @brief Remove shell quotes and escapes from a heredoc delimiter.
 * @param str Raw delimiter string.
 * @return Newly allocated unquoted delimiter, or NULL on failure.
 */
char	*remove_quotes_heredoc(char *str)
{
	char			*res;
	t_quotes_state	state;

	if (!str)
		return (NULL);
	state.i = 0;
	state.j = 0;
	state.quote = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[state.i])
	{
		if (state.quote)
			handle_inside_quote(str, res, &state);
		else
			handle_outside_quote(str, res, &state);
	}
	res[state.j] = '\0';
	return (res);
}
