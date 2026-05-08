/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 14:06:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 02:13:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

/**
 * @brief Advances a pointer past any non-digit characters.
 */
static char	*skip_to_digit(char *p)
{
	while (*p && !ft_isdigit(*p))
		p++;
	return (p);
}

/**
 * @brief Advances a pointer past any digit characters.
 */
static char	*skip_digits(char *p)
{
	while (*p && ft_isdigit(*p))
		p++;
	return (p);
}

/**
 * @brief Parses the XPM header string "W H COLORS CPP" robustly.
 */
int	parse_xpm_header(t_xpm *xpm, char *line)
{
	char	*p;

	p = line + 1;
	p = skip_to_digit(p);
	xpm->tex->size.x = (size_t)ft_atoi(p);
	p = skip_to_digit(skip_digits(p));
	xpm->tex->size.y = (size_t)ft_atoi(p);
	p = skip_to_digit(skip_digits(p));
	xpm->ncolors = (size_t)ft_atoi(p);
	p = skip_to_digit(skip_digits(p));
	xpm->cpp = (size_t)ft_atoi(p);
	if (xpm->tex->size.x == 0 || xpm->tex->size.y == 0
		|| xpm->ncolors == 0 || xpm->cpp == 0)
		return (1);
	return (0);
}

/**
 * @brief Parses the entire XPM color palette from the parser stream.
 */
t_xpm_color	*parse_xpm_palette(t_xpm *xpm)
{
	char	*line;
	size_t	i;

	xpm->colors = ft_calloc(xpm->ncolors, sizeof(t_xpm_color));
	if (!xpm->colors)
		return (NULL);
	i = 0;
	while (i < xpm->ncolors && parser_read_line_alloc(xpm->parser, &line))
	{
		if (line[0] != '"')
		{
			free(line);
			continue ;
		}
		xpm->colors[i].key = xpm_token_key(line + 1, xpm->cpp);
		xpm->colors[i].color = xpm_parse_color(line, xpm->cpp);
		free(line);
		i++;
	}
	if (i != xpm->ncolors)
		return (free(xpm->colors), xpm->colors = NULL, NULL);
	return (xpm->colors);
}
