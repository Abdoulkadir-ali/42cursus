/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_strict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 01:47:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:47:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	skip_sign(const char *s, int *i, int *sign)
{
	*sign = 1;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign = -1;
		(*i)++;
	}
	if (!s[*i] || (s[*i] != '.' && (s[*i] < '0' || s[*i] > '9')))
		return (0);
	return (1);
}

static void	apply_exp(double *val, int exp_v, int esign)
{
	if (exp_v > 38)
		exp_v = 38;
	while (exp_v-- > 0)
	{
		if (esign > 0)
			*val *= 10.0;
		else
			*val /= 10.0;
	}
}

static int	parse_exp(const char *s, int *i, double *val)
{
	int	esign;
	int	exp_v;

	if (s[*i] == 'e' || s[*i] == 'E')
	{
		(*i)++;
		esign = 1;
		if (s[*i] == '+' || s[*i] == '-')
		{
			if (s[*i] == '-')
				esign = -1;
			(*i)++;
		}
		if (s[*i] < '0' || s[*i] > '9')
			return (0);
		exp_v = 0;
		while (s[*i] >= '0' && s[*i] <= '9')
			exp_v = exp_v * 10 + (s[(*i)++] - '0');
		apply_exp(val, exp_v, esign);
	}
	return (1);
}

static void	parse_parts(const char *s, int *i, double int_f_d[3])
{
	int_f_d[0] = 0.0;
	while (s[*i] >= '0' && s[*i] <= '9')
		int_f_d[0] = int_f_d[0] * 10.0 + (s[(*i)++] - '0');
	int_f_d[1] = 0.0;
	int_f_d[2] = 1.0;
	if (s[*i] == '.')
	{
		(*i)++;
		while (s[*i] >= '0' && s[*i] <= '9')
		{
			int_f_d[1] = int_f_d[1] * 10.0 + (s[(*i)++] - '0');
			int_f_d[2] *= 10.0;
		}
	}
}

float	ft_atof_strict(const char *s, int *ok)
{
	int		i;
	int		sign;
	double	int_f_d[3];
	double	val;

	i = 0;
	*ok = 0;
	if (!s || !skip_sign(s, &i, &sign))
		return (0.0f);
	parse_parts(s, &i, int_f_d);
	val = sign * (int_f_d[0] + int_f_d[1] / int_f_d[2]);
	if (!parse_exp(s, &i, &val) || s[i] != '\0')
		return (0.0f);
	*ok = 1;
	return ((float)val);
}
