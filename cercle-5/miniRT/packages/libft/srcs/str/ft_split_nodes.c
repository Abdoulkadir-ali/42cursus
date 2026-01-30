/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_nodes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:56 by abdali            #+#    #+#             */
/*   Updated: 2026/01/30 18:05:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static const char	*skip_separators(const char *s, const char *sep)
{
	if (!s || !sep)
		return (s);
	while (*s && ft_strchr(sep, *s))
		s++;
	return (s);
}

static size_t	get_token_len(const char *s, const char *sep,
		size_t (*match)(const void *, const void *))
{
	size_t	len;

	if (!s)
		return (0);
	len = match(s, sep);
	if (len == 0)
		len = 1;
	return (len);
}

static t_nodes	*append_token(t_nodes *list, const char *s, size_t len)
{
	t_nodes	*new;

	new = ft_lstnew(ft_strldup((char *)s, len));
	if (!new)
	{
		ft_lstclear(&list, free);
		return (NULL);
	}
	ft_lstadd_back(&list, new);
	return (list);
}

t_nodes	*ft_split_nodes(char const *s, char *sep, size_t (*match)(const void *,
			const void *))
{
	t_nodes	*list;
	size_t	len;

	if (!s)
		return (NULL);
	if (!sep)
		sep = " ";
	if (!match)
		match = &any_match;
	list = NULL;
	while (*s)
	{
		s = skip_separators(s, sep);
		if (!*s)
			break ;
		len = get_token_len(s, sep, match);
		list = append_token(list, s, len);
		if (!list)
			return (NULL);
		s += len;
	}
	return (list);
}
