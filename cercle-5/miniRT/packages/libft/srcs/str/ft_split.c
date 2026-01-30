/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 20:06:56 by abdali            #+#    #+#             */
/*   Updated: 2026/01/30 16:52:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_words(const char *str, char c)
{
	unsigned int	w;

	w = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (*str)
			w++;
		while (*str && *str != c)
			str++;
	}
	return (w);
}

void	*free_split(char **strs)
{
	char	**start;

	start = strs;
	while (*strs)
		free(*strs++);
	free(start);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	unsigned int	w;
	unsigned int	i;
	char			**strs;

	strs = malloc(sizeof(char *) * (ft_count_words(str, c) + 1));
	if (!strs)
		return (NULL);
	w = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		if (!*str)
			break ;
		i = 0;
		while (str[i] && str[i] != c)
			i++;
		strs[w] = ft_strndup(str, i);
		if (!strs[w++])
			return (free_split(strs));
		str = str + i;
	}
	strs[w] = NULL;
	return (strs);
}
