/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:56:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 22:53:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	**duplicate_env(char **envp)
{
	int		env_count;
	char	**heap_env;
	int		i;

	env_count = 0;
	while (envp[env_count])
		env_count++;
	heap_env = malloc(sizeof(char *) * (env_count + 1));
	if (!heap_env)
		return (NULL);
	i = 0;
	while (i < env_count)
	{
		heap_env[i] = ft_strdup(envp[i]);
		i++;
	}
	heap_env[i] = NULL;
	return (heap_env);
}

int	is_whitespace_only(char *str)
{
	while (str && *str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
