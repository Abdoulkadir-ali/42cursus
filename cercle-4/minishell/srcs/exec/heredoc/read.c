/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:26:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:32:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void read_heredoc_loop(char *delim, int fd, char **envp, int exit_code)
{
    char *line;
    char *stop_str;
    int quoted;

    quoted = is_quoted_delim(delim);
    if (quoted)
        stop_str = remove_quotes_heredoc(delim);
    else
        stop_str = expand_string(delim, envp, exit_code);
    if (!stop_str)
        stop_str = ft_strdup(delim);
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
                if (i >= 9999)
                    break;
            }
            if (i > 0)
            {
                if (buf[i - 1] == '\n')
                    buf[i - 1] = '\0';
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
            {
                ft_putstr_fd("minishell: warning: here-document delimited by end-of-file (wanted `", 2);
                ft_putstr_fd(stop_str, 2);
                ft_putendl_fd("')", 2);
            }
            break ;
        }
        if (!quoted)
        {
            char *expanded_candidate = expand_heredoc(line, envp, exit_code);
            if (ft_strncmp(expanded_candidate, stop_str, ft_strlen(stop_str) + 1) == 0)
            {
                free(expanded_candidate);
                free(line);
                break ;
            }
            ft_putendl_fd(expanded_candidate, fd);
            free(expanded_candidate);
        }
        else
        {
            if (ft_strncmp(line, stop_str, ft_strlen(stop_str) + 1) == 0)
            {
                free(line);
                break ;
            }
            ft_putendl_fd(line, fd);
        }
        free(line);
    }
    setup_signals(SIGNAL_INTERACTIVE);
    free(stop_str);
}

char *handle_heredoc_input(char *delim, char **envp, int exit_code)
{
    char *filename;
    int fd;

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
