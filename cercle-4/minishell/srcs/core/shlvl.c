/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_shlvl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 05:23:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

static int	find_shlvl_index(char **heap_env)
{
	int	i;

	i = 0;
	while (heap_env[i])
	{
		if (ft_strncmp(heap_env[i], "SHLVL=", 6) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static int	calculate_shlvl(int existing_shlvl)
{
	int	shlvl;

	shlvl = existing_shlvl + 1;
	if (shlvl > 1000)
		shlvl = 1;
	return (shlvl);
}

static void	update_shlvl_entry(char **heap_env, int idx, int shlvl)
{
	char	shlvl_str[20];

	sprintf(shlvl_str, "SHLVL=%d", shlvl);
	free(heap_env[idx]);
	heap_env[idx] = ft_strdup(shlvl_str);
}

static void	add_shlvl_entry(char **heap_env, int shlvl)
{
	int		i;
	char	shlvl_str[20];

	i = 0;
	while (heap_env[i])
		i++;
	sprintf(shlvl_str, "SHLVL=%d", shlvl);
	heap_env[i] = ft_strdup(shlvl_str);
	heap_env[i + 1] = NULL;
}

void	add_shlvl_to_env(char **heap_env)
{
	int	existing_idx;
	int	shlvl;

	existing_idx = find_shlvl_index(heap_env);
	if (existing_idx != -1)
	{
		shlvl = calculate_shlvl(atoi(heap_env[existing_idx] + 6));
		update_shlvl_entry(heap_env, existing_idx, shlvl);
	}
	else
	{
		shlvl = 1;
		add_shlvl_entry(heap_env, shlvl);
	}
}
