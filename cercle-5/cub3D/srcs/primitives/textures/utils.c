/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 18:00:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

/**
 * @brief Converts a string token of length cpp into a unique unsigned int key.
 */
unsigned int	xpm_token_key(const char *s, size_t cpp)
{
	unsigned int	key;

	key = 0;
	while (cpp--)
		key = (key << 8) | (unsigned char)*s++;
	return (key);
}

/**
 * @brief Parses a hex color string into an ARGB unsigned int.
 */
static unsigned int	parse_hex_color(const char *s)
{
	unsigned int	color;
	size_t			i;

	if (*s == '#')
		s++;
	color = 0;
	i = 0;
	while (i < 6 && s[i])
	{
		color <<= 4;
		if (s[i] >= '0' && s[i] <= '9')
			color |= s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			color |= s[i] - 'a' + 10;
		else if (s[i] >= 'A' && s[i] <= 'F')
			color |= s[i] - 'A' + 10;
		i++;
	}
	return (color);
}

/**
 * @brief Extracts color data from an XPM color line.
 */
unsigned int	xpm_parse_color(const char *line, size_t cpp)
{
	char	*p;

	p = ft_strnstr(line + 1 + cpp, " c ", 64);
	if (!p)
		return (0);
	p += 3;
	while (*p && ft_isspace(*p))
		p++;
	if (ft_strnstr(p, "None", 4))
		return (0);
	return (COL_ALPHA | parse_hex_color(p));
}

/**
 * @brief Frees a null-terminated array of strings.
 */
void	free_tab(char **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}
