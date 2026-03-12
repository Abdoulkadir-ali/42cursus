/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 15:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 00:26:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Detect whether a string still contains active wildcard metacharacters.
 * @param str String under inspection.
 * @return 1 when `*` or `?` remains active, otherwise 0.
 */
bool	is_wildcard(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\001')
		{
			i += 2;
			continue ;
		}
		if (str[i] == '*' || str[i] == '?')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Remember the latest `*` position for future backtracking.
 * @param pattern Address of the current pattern cursor.
 * @param str Address of the current string cursor.
 * @param star Output pointer storing the most recent star position.
 * @param str_start Output pointer storing the retry point in the string.
 * @return This function does not return a value.
 */
static void	set_star(char **pattern, char **str, char **star, char **str_start)
{
	*star = *pattern;
	(*pattern)++;
	*str_start = *str;
}

/**
 * @brief Advance both the pattern and filename cursors by one character.
 * @param pattern Address of the current pattern cursor.
 * @param str Address of the current string cursor.
 * @return This function does not return a value.
 */
static void	advance_both(char **pattern, char **str)
{
	(*pattern)++;
	(*str)++;
}

/**
 * @brief Retry the match from the character after the last remembered star.
 * @param pattern Address of the current pattern cursor.
 * @param str Address of the current string cursor.
 * @param star Pointer to the most recent star position.
 * @param str_start Pointer to the current retry position in the string.
 * @return This function does not return a value.
 */
static void	backtrack_to_star(char **pattern, char **str, char **star,
		char **str_start)
{
	*pattern = *star + 1;
	*str = ++(*str_start);
}

/**
 * @brief Run the core wildcard matching loop with star backtracking.
 * @param pattern Address of the current pattern cursor.
 * @param str Address of the current filename cursor.
 * @param star Address of the most recent star position.
 * @param str_start Address of the retry point paired with that star.
 * @return 1 when the string is consumed consistently, otherwise 0.
 */
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
