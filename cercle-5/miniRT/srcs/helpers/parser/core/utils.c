/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/12 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parser_skip_spaces(t_parser *p)
{
	char	c;
	int		count;

	count = 0;
	c = parser_peek(p);
	while (c)
	{
		if (ft_isspace(c))
		{
			parser_advance(p);
			c = parser_peek(p);
			count++;
			if (count > 1000000)
			{
				printf("CRITICAL ERROR: parser_skip_spaces loop\n");
				fflush(stdout);
				break ;
			}
		}
		else
			break ;
	}
}

bool	parser_match(t_parser *p, char expected)
{
	parser_skip_spaces(p);
	if (parser_peek(p) == expected)
	{
		parser_advance(p);
		return (true);
	}
	return (false);
}

bool	parser_get_line(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	i = 0;
	c = parser_peek(p);
	if (!c && p->eof)
		return (false);
	while (c && c != '\n' && c != '\r' && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	if (c == '\r')
	{
		parser_advance(p);
		c = parser_peek(p);
	}
	if (c == '\n')
		parser_advance(p);
	buf[i] = '\0';
	return (true);
}

/**
 * @brief Aggressive word extraction: skips leading spaces and reads up to whitespace.
 */
bool	parser_get_next_word(t_parser *p, char *buf, size_t max_len)
{
	size_t	i;
	char	c;

	parser_skip_spaces(p);
	i = 0;
	c = parser_peek(p);
	if (!c && p->eof)
		return (false);
	while (c && !ft_isspace(c) && i < max_len - 1)
	{
		buf[i++] = c;
		parser_advance(p);
		c = parser_peek(p);
	}
	buf[i] = '\0';
	return (i > 0);
}

double	ft_atof_advance(char **s)
{
	double	res;
	double	fraction;
	double	divisor;
	int		sign;

	res = 0.0;
	sign = 1;
	while (**s && ft_isspace(**s))
		(*s)++;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	while (ft_isdigit(**s))
	{
		res = res * 10.0 + (**s - '0');
		(*s)++;
	}
	if (**s == '.')
	{
		(*s)++;
		fraction = 0.0;
		divisor = 10.0;
		while (ft_isdigit(**s))
		{
			fraction += (**s - '0') / divisor;
			divisor *= 10.0;
			(*s)++;
		}
		res += fraction;
	}
	return (res * sign);
}

int	ft_atoi_advance(char **s)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (**s && ft_isspace(**s))
		(*s)++;
	if (**s == '-' || **s == '+')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	while (ft_isdigit(**s))
	{
		res = res * 10 + (**s - '0');
		(*s)++;
	}
	return (res * sign);
}
