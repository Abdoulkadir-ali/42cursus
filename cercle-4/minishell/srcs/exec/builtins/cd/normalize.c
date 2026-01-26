/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:42:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 03:48:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*build_base_path(const char *path, char **envp, int *leading_slashes)
{
	char	*base;
	char	*pwd;
	char	*cwd_dup;
	int		count;

	*leading_slashes = 0;
	if (path[0] == '/')
	{
		count = 0;
		while (path[count] == '/')
			count++;
		base = ft_strdup(path);
		if (!base)
			return (NULL);
		*leading_slashes = (count == 2) ? 2 : 1;
		return (base);
	}
	pwd = get_env_val_simple("PWD", envp);
	if (pwd && pwd[0] != '\0')
	{
		base = join_paths(pwd, path);
		*leading_slashes = (base[0] == '/'
				&& base[1] == '/') ? 2 : ((base[0] == '/') ? 1 : 0);
		return (base);
	}
	cwd_dup = get_cwd_dup();
	if (cwd_dup && cwd_dup[0] != '\0')
	{
		base = join_paths(cwd_dup, path);
		free(cwd_dup);
		*leading_slashes = (base[0] == '/'
				&& base[1] == '/') ? 2 : ((base[0] == '/') ? 1 : 0);
		return (base);
	}
	free(cwd_dup);
	base = ft_strdup(path);
	return (base);
}

char	**collect_components(const char *base, int *count)
{
	char	**stack;
	int		len;
	int		pos;
	int		start;
	int		comp_len;
	char	*comp;
	int		j;

	stack = malloc(sizeof(char *) * 1024);
	if (!stack)
	{
		*count = 0;
		return (NULL);
	}
	j = 0;
	len = ft_strlen(base);
	pos = 0;
	while (pos < len)
	{
		while (pos < len && base[pos] == '/')
			pos++;
		if (pos >= len)
			break ;
		start = pos;
		while (pos < len && base[pos] != '/')
			pos++;
		comp_len = pos - start;
		if (comp_len == 0)
			continue ;
		comp = ft_substr(base, start, comp_len);
		if (!comp)
			continue ;
		if (ft_strcmp(comp, ".") == 0)
		{
			free(comp);
			continue ;
		}
		if (ft_strcmp(comp, "..") == 0)
		{
			free(comp);
			if (j > 0)
				free(stack[--j]);
			continue ;
		}
		stack[j++] = comp;
	}
	*count = j;
	return (stack);
}

char	*build_path_from_stack(char **stack, int count, int leading_slashes)
{
	char	*res;
	char	*tmp;
	char	*pref;
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
	if (leading_slashes)
	{
		pref = (leading_slashes == 2) ? ft_strdup("//") : ft_strdup("/");
		tmp = ft_strjoin(pref, res);
		free(pref);
		free(res);
		res = tmp;
	}
	i = 0;
	while (i < count)
		free(stack[i++]);
	free(stack);
	return (res);
}

char	*normalize_logical(const char *path, char **envp)
{
	char	**stack;
	int		count;
	char	*base;
	char	*res;
	int		leading_slashes;

	if (!path)
		return (NULL);
	base = build_base_path(path, envp, &leading_slashes);
	if (!base)
		return (ft_strdup(path));
	stack = collect_components(base, &count);
	free(base);
	if (!stack)
		return (ft_strdup(path));
	if (count == 0)
		return ((leading_slashes == 2) ? ft_strdup("//") : ft_strdup("/"));
	res = build_path_from_stack(stack, count, leading_slashes);
	return (res);
}
