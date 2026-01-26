/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:42:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:45:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*handle_root_path(int leading_slashes)
{
	if (leading_slashes == 2)
		return (ft_strdup("//"));
	else
		return (ft_strdup("/"));
}

static char	*norm_components(char **stack, int count, int leading_slashes)
{
	char	*res;

	if (count == 0)
	{
		free(stack);
		return (handle_root_path(leading_slashes));
	}
	res = build_path_from_stack(stack, count, leading_slashes);
	return (res);
}

char	*normalize_logical(const char *path, t_shell_state *state)
{
	char	**stack;
	int		count;
	char	*base;
	int		leading_slashes;

	if (!path)
		return (NULL);
	base = build_base_path(path, state, &leading_slashes);
	if (!base)
		return (ft_strdup(path));
	stack = collect_components(base, &count);
	free(base);
	if (!stack)
		return (ft_strdup(path));
	return (norm_components(stack, count, leading_slashes));
}
