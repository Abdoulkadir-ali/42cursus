/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:09:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*build_path_loop(char **stack, int count)
{
	char	*res;
	char	*tmp;
	int		i;

	res = ft_strdup(stack[0]);
	i = 1;
	while (i < count)
	{
		tmp = ft_strjoin(res, "/");
		free(res);
		res = ft_strjoin(tmp, stack[i]);
		free(tmp);
		i++;
	}
	return (res);
}

static char	*add_prefix(char *res, int leading_slashes)
{
	char	*tmp;
	char	*pref;

	if (leading_slashes == 2)
		pref = ft_strdup("//");
	else
		pref = ft_strdup("/");
	tmp = ft_strjoin(pref, res);
	free(pref);
	free(res);
	return (tmp);
}

static void	free_stack(char **stack, int count)
{
	int	i;

	i = 0;
	while (i < count)
		free(stack[i++]);
	free(stack);
}

char	*build_path_from_stack(char **stack, int count, int leading_slashes)
{
	char	*res;

	if (count == 0)
	{
		free(stack);
		if (leading_slashes == 2)
			return (ft_strdup("//"));
		else
			return (ft_strdup("/"));
	}
	res = build_path_loop(stack, count);
	if (leading_slashes)
		res = add_prefix(res, leading_slashes);
	free_stack(stack, count);
	return (res);
}
