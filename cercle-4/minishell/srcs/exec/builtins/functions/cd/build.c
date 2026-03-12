/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:15:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Free a component stack allocated during path normalization.
 * @param stack Array of directory component strings.
 * @param count Number of valid entries stored in the stack.
 * @return This function does not return a value.
 */
static void	free_stack(char **stack, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
		free(stack[i++]);
	free(stack);
}

/**
 * @brief Compute the final string length for a normalized path.
 * @param stack Array of normalized directory components.
 * @param count Number of valid components in the stack.
 * @param leading_slashes Number of leading slashes to preserve.
 * @return Total string length excluding the trailing null byte.
 */
static size_t	calc_len(char **stack, size_t count, size_t leading_slashes)
{
	size_t	len;
	size_t	i;

	i = 0;
	len = 0;
	while (leading_slashes-- > 0)
		len++;
	while (i < count)
	{
		len += ft_strlen(stack[i]);
		if (i < count - 1)
			len++;
		i++;
	}
	return (len);
}

/**
 * @brief Copy normalized components into the destination path buffer.
 * @param res Destination buffer sized for the normalized path.
 * @param stack Array of normalized directory components.
 * @param count Number of valid components in the stack.
 * @param leading_slashes Number of leading slashes to preserve.
 * @return This function does not return a value.
 */
static void	fill_path(char *res, char **stack, size_t count, size_t leading_slashes)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	ptr = res;
	if (leading_slashes > 0)
	{
		*ptr++ = '/';
		if (leading_slashes == 2)
			*ptr++ = '/';
	}
	i = 0;
	while (i < count)
	{
		len = ft_strlen(stack[i]);
		ft_memcpy(ptr, stack[i], len);
		ptr += len;
		if (i < count - 1)
			*ptr++ = '/';
		i++;
	}
	*ptr = '\0';
}

/**
 * @brief Build the final normalized path string from collected components.
 * @param stack Array of normalized directory components.
 * @param count Number of valid components in the stack.
 * @param leading_slashes Number of leading slashes to preserve.
 * @return Newly allocated normalized path, or NULL on allocation failure.
 */
char	*build_path_from_stack(char **stack, size_t count, size_t leading_slashes)
{
	char	*res;
	size_t	total_len;

	total_len = calc_len(stack, count, leading_slashes);
	res = malloc(total_len + 1);
	if (!res)
	{
		free_stack(stack, count);
		return (NULL);
	}
	fill_path(res, stack, count, leading_slashes);
	free_stack(stack, count);
	return (res);
}
