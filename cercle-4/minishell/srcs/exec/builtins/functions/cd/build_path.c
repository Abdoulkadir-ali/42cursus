/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:24:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_stack(char **stack, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(stack[i++]);
	free(stack);
}

static size_t	calc_len(char **stack, int count, int leading_slashes)
{
	size_t	len;
	int		i;

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

static void	fill_path(char *res, char **stack, int count, int leading_slashes)
{
	char	*ptr;
	int		i;
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

char	*build_path_from_stack(char **stack, int count, int leading_slashes)
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
