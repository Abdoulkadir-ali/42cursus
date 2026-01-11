/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 14:44:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*generate_tmp_filename(void)
{
	static int	i;
	char		*num;
	char		*name;

	num = ft_itoa(i++);
	name = ft_strjoin("/tmp/.minishell_heredoc_", num);
	free(num);
	return (name);
}

static int is_quoted_delim(const char *delim)
{
	if (!delim)
		return 0;
	int i = 0;
	while (delim[i]) {
		if (delim[i] == '\'' || delim[i] == '"' || delim[i] == '\\')
			return 1;
		i++;
	}
	return 0;
}

static char *remove_quotes_heredoc(char *str)
{
	char *res;
	int i = 0, j = 0;
	char quote = 0;
	
	if (!str) return NULL;
	res = malloc(ft_strlen(str) + 1);
	if (!res) return NULL;
	
	while (str[i])
	{
		if (quote)
		{
			if (str[i] == quote)
			{
				quote = 0;
				i++;
			}
			else
			{
				res[j++] = str[i];
				i++;
			}
		}
		else
		{
			if (str[i] == '\\')
			{
				i++;
				if (str[i])
				{
					res[j++] = str[i];
					i++;
				}
			}
			else if (str[i] == '\'' || str[i] == '"')
			{
				quote = str[i];
				i++;
			}
			else
			{
				res[j++] = str[i];
				i++;
			}
		}
	}
	res[j] = '\0';
	return (res);
}

static void read_heredoc_loop(char *delim, int fd, char **envp, int exit_code)
{
	char	*line;
	char	*stop_str;
	int		quoted;

	quoted = is_quoted_delim(delim);
	if (quoted)
		stop_str = remove_quotes_heredoc(delim);
	else
		stop_str = expand_string(delim, envp, exit_code);
	
	if (!stop_str) stop_str = ft_strdup(delim);
	setup_signals(SIGNAL_HEREDOC);
	while (1)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
		{
			char *buf = ft_calloc(10000, 1);
			int i = 0;
			char c;
			while (read(STDIN_FILENO, &c, 1) > 0)
			{
				buf[i++] = c;
				if (c == '\n')
					break;
				if (i >= 9999) break;
			}
			if (i > 0)
			{
				if (buf[i - 1] == '\n') buf[i - 1] = '\0';
				line = buf;
			}
			else
			{
				free(buf);
				line = NULL;
			}
		}
		if (!line)
		{
			if (g_last_signal != 130)
				ft_putendl_fd("minishell: warning: here-document delimited by end-of-file", 2);
			break ;
		}
		if (ft_strncmp(line, stop_str, ft_strlen(stop_str) + 1) == 0)
		{
			free(line);
			break ;
		}
		if (!quoted)
		{
			char *expanded = expand_heredoc(line, envp, exit_code);
			ft_putendl_fd(expanded, fd);
			free(expanded);
		}
		else
		{
			ft_putendl_fd(line, fd);
		}
		free(line);
	}
	setup_signals(SIGNAL_INTERACTIVE);
	free(stop_str);
}

static char	*handle_heredoc_input(char *delim, char **envp, int exit_code)
{
	char	*filename;
	int		fd;

	filename = generate_tmp_filename();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc tmp");
		free(filename);
		return (NULL);
	}
	read_heredoc_loop(delim, fd, envp, exit_code);
	close(fd);
	if (g_last_signal == 130)
	{
		unlink(filename);
		free(filename);
		return (NULL);
	}
	return (filename);
}

int	scan_heredocs(t_nodes *ast_node)
{
	t_ast	*node;
	char	*tmp_file;

	if (!ast_node)
		return (0);
	node = (t_ast *)ast_node->content;
	if (node->type == TOKEN_HEREDOC)
	{
		extern char **g_envp;
		extern int g_exit_code;
		tmp_file = handle_heredoc_input(node->args[0], g_envp, g_exit_code);
		if (!tmp_file)
			return (1);
		free(node->args[0]);
		node->args[0] = tmp_file;
		node->type = TOKEN_RED_IN;
	}
	if (scan_heredocs(node->left) || scan_heredocs(node->right))
		return (1);
	return (0);
}
