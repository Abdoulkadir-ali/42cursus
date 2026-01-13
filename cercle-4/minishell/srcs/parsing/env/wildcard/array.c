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

static void	append_to_list(t_nodes **list, char *str)
{
	ft_lstadd_back(list, ft_lstnew(ft_strdup(str)));
}

static void	process_wildcard(char *arg, t_nodes **list)
{
	DIR				*dir;
	struct dirent	*entry;
	int				match;

	match = 0;
	dir = opendir(".");
	if (dir)
	{
		while ((entry = readdir(dir)))
		{
			if (entry->d_name[0] == '.' && arg[0] != '.')
				continue ;
			if (ft_strcmp(entry->d_name, arg) == 0)
				continue ;
			if (match_pattern(arg, entry->d_name))
			{
				append_to_list(list, entry->d_name);
				match = 1;
			}
		}
		closedir(dir);
	}
	if (!match)
		append_to_list(list, arg);
}

char	**expand_wildcards(char **args)
{
	t_nodes	*list;
	int		len;
	char	**result;
	t_nodes	*tmp;
	int		i;

	list = NULL;
	for (i = 0; args && args[i]; i++)
	{
		if (is_wildcard(args[i]))
			process_wildcard(args[i], &list);
		else
			append_to_list(&list, args[i]);
	}
	sort_list(&list);
	len = ft_lstsize(list);
	result = malloc(sizeof(char *) * (len + 1));
	tmp = list;
	for (i = 0; i < len; i++)
	{
		result[i] = tmp->content;
		tmp = tmp->next;
	}
	result[len] = NULL;
	ft_lstclear(&list, NULL);
	return (result);
}
