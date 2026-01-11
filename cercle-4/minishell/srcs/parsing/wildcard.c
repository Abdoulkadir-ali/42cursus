/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 15:51:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <dirent.h>

static int	match_pattern(char *pattern, char *str)
{
	char *star = NULL;
	char *str_start = (char *)str;
	int attempts = 0;
	while (*str) {
		if (attempts++ > 100000) return 0;  // Prevent infinite loop
		if (*pattern == '*') {
			star = (char *)pattern;
			pattern++;
			str_start = (char *)str;
		} else if (*pattern == *str) {
			pattern++;
			str++;
		} else if (star) {
			pattern = star + 1;
			str = ++str_start;
		} else {
			return 0;
		}
	}
	while (*pattern == '*') pattern++;
	return *pattern == '\0';
}

int	is_wildcard(const char *str)
{
	int i = 0;
	while (str[i]) {
		if (str[i] == '*' && str[i] != '\\')
			return 1;
		i++;
	}
	return 0;
}

static void	sort_list_char(char **list)
{
	int	i;
	int	j;
	char	*tmp;

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

char **expand_wildcards(char **args)
{
	DIR *dir;
	struct dirent *entry;
	char **result = NULL;
	int count = 0, i = 0, match = 0;
	int max_args = 0;
	while (args && args[max_args])
		max_args++;
	result = malloc(sizeof(char *) * (max_args + 256)); // generous buffer
	for (i = 0; args && args[i]; i++) {
		match = 0;
		if (is_wildcard(args[i])) {
			dir = opendir(".");
			if (dir) {
				while ((entry = readdir(dir))) {
					if (entry->d_name[0] == '.' && args[i][0] != '.')
						continue;
					// Prevent self-matching: don't match arg to itself
					if (ft_strcmp(entry->d_name, args[i]) == 0)
						continue;
					if (match_pattern(args[i], entry->d_name)) {
						result[count++] = ft_strdup(entry->d_name);
						match = 1;
					}
				}
				closedir(dir);
			}
			// If no match, keep the original arg
			if (!match)
				result[count++] = ft_strdup(args[i]);
		} else {
			result[count++] = ft_strdup(args[i]);
		}
	}
	sort_list_char(result);
	result[count] = NULL;
	return result;
}

static void	sort_list(t_nodes **list)
{
	t_nodes	*i;
	t_nodes	*j;
	char	*tmp;
	int		sort_attempts = 0;

	i = *list;
	while (i && sort_attempts++ < 10000)
	{
		j = i->next;
		while (j)
		{
			if (ft_strncmp((char *)i->content, (char *)j->content, ft_strlen((char *)i->content) + 1) > 0)
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

t_nodes	*expand_wildcard(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	t_nodes			*files;
	char			*dup;
	int				match_count = 0;

	if (ft_strchr(pattern, '*') == NULL)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = NULL;
	int entry_count = 0;
	   while ((entry = readdir(dir)) != NULL && entry_count++ < 10000)
	   {
		   if (entry->d_name[0] == '.' && pattern[0] != '.')
			   continue ;
		   // Prevent self-matching: don't match the pattern itself
		   if (ft_strcmp(entry->d_name, pattern) == 0)
			   continue;
		   if (match_pattern(pattern, entry->d_name))
		   {
			   if (match_count++ > 100)
				   continue;
			   dup = ft_strdup(entry->d_name);
			   ft_lstadd_back(&files, ft_lstnew(dup));
		   }
	   }
	closedir(dir);
	if (!files)
		return (NULL); // Or return wildcard itself if no match? Bash returns literal pattern.
	sort_list(&files);
	return (files);
}
