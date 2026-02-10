/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 23:27:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	handle_dotdot(char **stack, int *j)
{
	if (*j > 0)
	{
		free(stack[--(*j)]);
	}
}

static int	add_component(char **stack, int *j, const char *comp)
{
	if (ft_strcmp(comp, ".") == 0)
	{
		return (0);
	}
	if (ft_strcmp(comp, "..") == 0)
	{
		handle_dotdot(stack, j);
		return (0);
	}
	stack[(*j)++] = ft_strdup(comp);
	return (1);
}

static char	*extract_next_component(const char *base, size_t *pos)
{
	size_t	start;
	size_t	comp_len;
	size_t	l;
	char	*comp;

	l = ft_strlen(base);
	while (*pos < l && base[*pos] == '/')
		(*pos)++;
	if (*pos >= l)
		return (NULL);
	start = *pos;
	while (*pos < l && base[*pos] != '/')
		(*pos)++;
	comp_len = *pos - start;
	if (comp_len == 0)
		return (NULL);
	comp = ft_substr(base, start, comp_len);
	return (comp);
}

static void	process_components(const char *base, char **stack, int *count)
{
	size_t	pos;
	char	*comp;

	pos = 0;
	comp = extract_next_component(base, &pos);
	while (comp)
	{
		add_component(stack, count, comp);
		free(comp);
		comp = extract_next_component(base, &pos);
	}
}

char	**collect_components(const char *base, int *count)
{
	char	**stack;

	stack = malloc(sizeof(char *) * 1024);
	if (!stack)
	{
		*count = 0;
		return (NULL);
	}
	*count = 0;
	process_components(base, stack, count);
	stack[*count] = NULL;
	return (stack);
}
