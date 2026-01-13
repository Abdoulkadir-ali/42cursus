/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 02:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/* detect whether a string contains an unescaped '*' */
static int	is_wildcard(const char *str)
{
    int	i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '*' && str[i] != '\\')
            return (1);
        i++;
    }
    return (0);
}

/* local copy of match_pattern used to test entries against a pattern */
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

/* simple alphabetical sort for a null-terminated array of strings */
static void	sort_list_char(char **list)
{
    int	 i;
    int	 j;
    char *tmp;

    i = 0;
    while (list[i])
    {
        j = i + 1;
        while (list[j])
        {
            if (ft_strcmp(list[i], list[j]) > 0)
            {
                tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
            }
            j++;
        }
        i++;
    }
}

/* public: expand a NULL-terminated argv-style array by wildcards */
char	**expand_wildcards(char **args)
{
    DIR		*dir;
    struct dirent	*entry;
    char	**result;
    int	count;
    int	i;
    int	match;
    int	max_args;

    result = NULL;
    count = 0;
    i = 0;
    match = 0;
    max_args = 0;
    while (args && args[max_args])
        max_args++;
    result = malloc(sizeof(char *) * (max_args + 256));
    for (i = 0; args && args[i]; i++)
    {
        match = 0;
        if (is_wildcard(args[i]))
        {
            dir = opendir(".");
            if (dir)
            {
                while ((entry = readdir(dir)))
                {
                    if (entry->d_name[0] == '.' && args[i][0] != '.')
                        continue ;
                    if (ft_strcmp(entry->d_name, args[i]) == 0)
                        continue ;
                    if (match_pattern((char *)args[i], entry->d_name))
                    {
                        result[count++] = ft_strdup(entry->d_name);
                        match = 1;
                    }
                }
                closedir(dir);
            }
            if (!match)
                result[count++] = ft_strdup(args[i]);
        }
        else
        {
            result[count++] = ft_strdup(args[i]);
        }
    }
    sort_list_char(result);
    result[count] = NULL;
    return (result);
}
