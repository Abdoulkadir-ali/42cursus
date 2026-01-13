/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:37:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*generate_tmp_filename(void)
{
    char tmpl[] = "/tmp/.minishell_heredoc_XXXXXX";
    int fd;

    fd = mkstemp(tmpl);
    if (fd == -1)
        return (NULL);
    fchmod(fd, 0644);
    close(fd);
    return (ft_strdup(tmpl));
}

int is_quoted_delim(const char *delim)
{
    int i;

    if (!delim)
        return (0);
    i = 0;
    while (delim[i])
    {
        if (delim[i] == '\'' || delim[i] == '"' || delim[i] == '\\')
            return (1);
        i++;
    }
    return (0);
}

char *remove_quotes_heredoc(char *str)
{
    char *res;
    int i;
    int j;
    char quote;

    if (!str)
        return (NULL);
    i = 0;
    j = 0;
    quote = 0;
    res = malloc(ft_strlen(str) + 1);
    if (!res)
        return (NULL);
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
                res[j++] = str[i++];
        }
        else
        {
            if (str[i] == '\\')
            {
                i++;
                if (str[i])
                    res[j++] = str[i++];
            }
            else if (str[i] == '\'' || str[i] == '"')
                quote = str[i++];
            else
                res[j++] = str[i++];
        }
    }
    res[j] = '\0';
    return (res);
}
