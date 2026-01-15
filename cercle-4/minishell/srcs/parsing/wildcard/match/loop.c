/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 03:54:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_wildcard(const char *str)
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

static void	set_star(char **pattern, char **str, char **star, char **str_start)
{
	*star = *pattern;
	(*pattern)++;
	*str_start = *str;
}

static void	advance_both(char **pattern, char **str)
{
	(*pattern)++;
	(*str)++;
}

static void	backtrack_to_star(char **pattern, char **str, char **star,
		char **str_start)
{
	*pattern = *star + 1;
	*str = ++(*str_start);
}

int	match_loop(char **pattern, char **str, char **star,
		char **str_start)
{
	int	dattempts;

	dattempts = 0;
	while (**str)
	{
		if (dattempts++ > 100000)
			return (0);
		if (**pattern == '*')
		{
			set_star(pattern, str, star, str_start);
			continue ;
		}
		if (**pattern == **str)
		{
			advance_both(pattern, str);
			continue ;
		}
		if (*star)
		{
			backtrack_to_star(pattern, str, star, str_start);
			continue ;
		}
		return (0);
	}
	return (1);
}
