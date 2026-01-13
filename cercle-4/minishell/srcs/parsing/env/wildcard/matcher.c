/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matcher.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:32:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* match_pattern: greedy '*' matcher used only in this translation unit */
static int	match_pattern(char *pattern, char *str)
{
    char	*star;
    char	*str_start;
    int	attempts;

    star = NULL;
    str_start = (char *)str;
    attempts = 0;
    while (*str)
    {
        if (attempts++ > 100000)
            return (0);
        if (*pattern == '*')
        {
            star = (char *)pattern;
            pattern++;
            str_start = (char *)str;
        }
        else if (*pattern == *str)
        {
            pattern++;
            str++;
        }
        else if (star)
        {
            pattern = star + 1;
            str = ++str_start;
        }
        else
            return (0);
    }
    while (*pattern == '*')
        pattern++;
    return (*pattern == '\0');
}

/* linked-list sort used only here */
static void	sort_list(t_nodes **list)
{
    t_nodes	*i;
    t_nodes	*j;
    char	*tmp;
    int		sort_attempts;

    sort_attempts = 0;
    i = *list;
    while (i && sort_attempts++ < 10000)
    {
        j = i->next;
        while (j)
        {
            if (ft_strncmp((char *)i->content, (char *)j->content,
                    ft_strlen((char *)i->content) + 1) > 0)
            {
                tmp = i->content;
                i->content = j->content;
                j->content = tmp;
            }
            j = j->next;
        }
        i = i->next;
    }
}

/* public: expand a single wildcard pattern into a t_nodes list (or NULL) */
t_nodes	*expand_wildcard(char *pattern)
{
    DIR		*dir;
    struct dirent	*entry;
    t_nodes	*files;
    char	*dup;
    int	match_count;
    int	entry_count;

    match_count = 0;
    if (ft_strchr(pattern, '*') == NULL)
        return (NULL);
    dir = opendir(".");
    if (!dir)
        return (NULL);
    files = NULL;
    entry_count = 0;
    while ((entry = readdir(dir)) != NULL && entry_count++ < 10000)
    {
        if (entry->d_name[0] == '.' && pattern[0] != '.')
            continue ;
        if (ft_strcmp(entry->d_name, pattern) == 0)
            continue ;
        if (match_pattern(pattern, entry->d_name))
        {
            if (match_count++ > 100)
                continue ;
            dup = ft_strdup(entry->d_name);
            ft_lstadd_back(&files, ft_lstnew(dup));
        }
    }
    closedir(dir);
    if (!files)
        return (NULL);
    sort_list(&files);
    return (files);
}
