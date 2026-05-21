/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 16:51:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	skip_ws_and_comma(char *line, int i)
{
	while (line[i] && (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r' && line[i] != '#'))
	{
		if (line[i] == ',')
		{
			i++;
			while (line[i] == ' ' || line[i] == '\t')
				i++;
			continue ;
		}
		i++;
	}
	return (i);
}

int	tokenize(char *line, char **tokens, int max_tokens)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] && count < max_tokens)
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
			|| line[i] == '\r')
			i++;
		if (!line[i] || line[i] == '#')
			break ;
		tokens[count++] = &line[i];
		i = skip_ws_and_comma(line, i);
		if (line[i])
		{
			if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
				|| line[i] == '\r' || line[i] == '#')
				line[i++] = '\0';
		}
	}
	return (count);
}

static int	split_triplet(char *buf, char **parts)
{
	int	i;
	int	j;
	int	c;

	i = 0;
	c = 0;
	while (c < 3)
	{
		j = i;
		while (buf[j] && buf[j] != ',')
			j++;
		if (c < 2 && !buf[j])
			return (0);
		if (buf[j] == ',')
			buf[j] = '\0';
		while (buf[i] == ' ' || buf[i] == '\t')
			i++;
		parts[c] = &buf[i];
		i = j + 1;
		c++;
	}
	return (1);
}

/* Parses "r,g,b" with each in [0,255]; returns t_vec3 in [0,1] floats. */
int	parse_color(const char *s, t_vec3 *out)
{
	char	buf[256];
	char	*parts[3];
	t_vec3i	v;
	int		ok;
	int		i;
	int		*vptr[3];

	if (!s || strlen(s) >= sizeof(buf))
		return (0);
	strcpy(buf, s);
	if (!split_triplet(buf, parts))
		return (0);
	vptr[0] = &v.x;
	vptr[1] = &v.y;
	vptr[2] = &v.z;
	i = -1;
	while (++i < 3)
	{
		*vptr[i] = ft_atoi_strict(parts[i], &ok);
		if (!ok || *vptr[i] < 0 || *vptr[i] > 255)
			return (0);
	}
	out->x = (v.x / 255.0f) * (v.x / 255.0f);
	out->y = (v.y / 255.0f) * (v.y / 255.0f);
	out->z = (v.z / 255.0f) * (v.z / 255.0f);
	return (1);
}

/* Parses "x,y,z" floats. */
int	parse_vec3(const char *s, t_vec3 *out)
{
	char	buf[256];
	char	*parts[3];
	int		ok;
	int		i;
	t_vec3	v;
	float	*vptr[3];

	if (!s || strlen(s) >= sizeof(buf))
		return (0);
	strcpy(buf, s);
	if (!split_triplet(buf, parts))
		return (0);
	vptr[0] = &v.x;
	vptr[1] = &v.y;
	vptr[2] = &v.z;
	i = -1;
	while (++i < 3)
	{
		*vptr[i] = ft_atof_strict(parts[i], &ok);
		if (!ok)
			return (0);
	}
	out->x = v.x;
	out->y = v.y;
	out->z = v.z;
	return (1);
}

int	parse_unit_vec3(const char *s, t_vec3 *out)
{
	if (!parse_vec3(s, out))
		return (0);
	if (out->x < -1.0f || out->x > 1.0f || out->y < -1.0f || out->y > 1.0f
		|| out->z < -1.0f || out->z > 1.0f)
		return (0);
	if (v3_dot(*out, *out) < 1e-6f)
		return (0);
	*out = v3_norm(*out);
	return (1);
}
