/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 03:02:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_wildcard(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\001')
		{
			i += 2;
			continue ;
		}
		if (str[i] == '*' || str[i] == '?')
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
	while (**str)
	{
		if (**pattern == '\001')
		{
			(*pattern)++;
			if (**pattern == **str)
				advance_both(pattern, str);
			else if (*star)
				backtrack_to_star(pattern, str, star, str_start);
			else
				return (0);
		}
		else if (**pattern == '*')
			set_star(pattern, str, star, str_start);
		else if (**pattern == '?' || **pattern == **str)
			advance_both(pattern, str);
		else if (*star)
			backtrack_to_star(pattern, str, star, str_start);
		else
			return (0);
	}
	return (1);
}
