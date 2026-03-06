/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 00:23:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

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

static char	*make_shlvl_str(int shlvl)
{
	char	*num;
	char	*entry;

	num = ft_itoa(shlvl);
	if (!num)
		return (NULL);
	entry = ft_strjoin("SHLVL=", num);
	free(num);
	return (entry);
}

static void	set_shlvl_entry(char **heap_env, int idx, int shlvl)
{
	char	*entry;

	entry = make_shlvl_str(shlvl);
	if (!entry)
		return ;
	if (idx >= 0)
	{
		free(heap_env[idx]);
		heap_env[idx] = entry;
	}
	else
	{
		idx = 0;
		while (heap_env[idx])
			idx++;
		heap_env[idx] = entry;
		heap_env[idx + 1] = NULL;
	}
}

void	add_shlvl_to_env(char **heap_env)
{
	int	existing_idx;
	int	shlvl;

	existing_idx = find_shlvl_index(heap_env);
	if (existing_idx != -1)
		shlvl = calculate_shlvl(ft_atoi(heap_env[existing_idx] + 6));
	else
		shlvl = 1;
	set_shlvl_entry(heap_env, existing_idx, shlvl);
}
