/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   components.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Remove the last kept component when `..` is encountered.
 * @param stack Stack of normalized path components.
 * @param j Current component count, updated in place.
 * @return This function does not return a value.
 */
static void	handle_dotdot(char **stack, size_t *j)
{
	if (*j > 0)
	{
		free(stack[--(*j)]);
	}
}

/**
 * @brief Apply one extracted path component to the normalization stack.
 * @param stack Stack of normalized path components.
 * @param j Current component count, updated in place.
 * @param comp Raw component extracted from the base path.
 * @param max Maximum number of components accepted in the stack.
 * @return 1 when a component is added, 0 when skipped, -1 on overflow.
 */
static int	add_component(char **stack, size_t *j, const char *comp, size_t max)
{
	if (ft_strcmp(comp, ".") == 0)
		return (0);
	if (ft_strcmp(comp, "..") == 0)
	{
		handle_dotdot(stack, j);
		return (0);
	}
	if (*j >= max - 1)
		return (-1);
	stack[(*j)++] = ft_strdup(comp);
	return (1);
}

/**
 * @brief Extract the next slash-delimited component from a path string.
 * @param base Path string currently being normalized.
 * @param pos Cursor advanced to the next unread position.
 * @return Newly allocated component string, or NULL when exhausted.
 */
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

/**
 * @brief Tokenize a base path into normalized components.
 * @param base Base path selected for logical normalization.
 * @param stack Destination stack of component strings.
 * @param count Number of stored components, updated in place.
 * @return This function does not return a value.
 */
static void	process_components(const char *base, char **stack, size_t *count)
{
	size_t	pos;
	char	*comp;

	pos = 0;
	comp = extract_next_component(base, &pos);
	while (comp)
	{
		if (add_component(stack, count, comp, CD_MAX_COMPONENTS) < 0)
		{
			free(comp);
			break ;
		}
		free(comp);
		comp = extract_next_component(base, &pos);
	}
}

/**
 * @brief Collect normalized path components from a base path string.
 * @param base Base path selected for logical normalization.
 * @param count Output number of collected components.
 * @return Newly allocated NULL-terminated component stack.
 */
char	**collect_components(const char *base, size_t *count)
{
	char	**stack;

	stack = malloc(sizeof(char *) * CD_MAX_COMPONENTS);
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
