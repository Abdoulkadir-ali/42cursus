/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 02:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:52:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	swap_contents(t_nodes *a, t_nodes *b)
{
	char	*tmp;

	tmp = a->content;
	a->content = b->content;
	b->content = tmp;
}

static void	sort_list(t_nodes **list)
{
	t_nodes	*i;
	t_nodes	*j;
	int		attempts;

	attempts = 0;
	i = *list;
	while (i && attempts++ < 10000)
	{
		j = i->next;
		while (j)
		{
			if (ft_strncmp((char *)i->content, (char *)j->content,
					ft_strlen((char *)i->content) + 1) > 0)
				swap_contents(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

t_nodes	*expand_wildcard(char *pattern)
{
	DIR		*dir;
	t_nodes	*files;

	if (ft_strchr(pattern, '*') == NULL)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (NULL);
	files = collect_matches(dir, pattern);
	closedir(dir);
	if (!files)
		return (NULL);
	sort_list(&files);
	return (files);
}
