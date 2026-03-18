/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:45 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:47 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Build the normalized representation for the filesystem root.
 * @param leading_slashes Number of leading slashes that must be preserved.
 * @return Newly allocated root path string.
 */
static char	*handle_root_path(size_t leading_slashes)
{
	if (leading_slashes == 2)
		return (ft_strdup("//"));
	else
		return (ft_strdup("/"));
}

/**
 * @brief Finalize a normalized path from collected components.
 * @param stack Stack of normalized components.
 * @param count Number of kept components.
 * @param leading_slashes Number of leading slashes to preserve.
 * @return Newly allocated normalized path string.
 */
static char	*norm_components(char **stack, size_t count, size_t leading_slashes)
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

/**
 * @brief Compute the logical cd destination for a path operand.
 * @param path Raw path operand passed to cd.
 * @param state Shell state used to build the logical base path.
 * @return Newly allocated normalized path, or a duplicate fallback.
 */
char	*normalize_logical(const char *path, t_shell_state *state)
{
	char	**stack;
	size_t	count;
	char	*base;
	size_t	leading_slashes;

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

/**
 * @brief Join two path fragments while preserving existing separators.
 * @param a Left-hand path fragment.
 * @param b Right-hand path fragment.
 * @return Newly allocated joined path string.
 */
char	*join_paths(const char *a, const char *b)
{
	char	*tmp;
	char	*res;

	if (!a || a[0] == '\0')
		return (ft_strdup(b));
	if (a[0] == '/' && a[1] == '\0')
		return (ft_strjoin("/", b));
	if (a[ft_strlen(a) - 1] == '/')
		return (ft_strjoin(a, b));
	tmp = ft_strjoin(a, "/");
	res = ft_strjoin(tmp, b);
	free(tmp);
	return (res);
}
