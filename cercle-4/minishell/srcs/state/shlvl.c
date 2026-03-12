/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/12 20:25:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "state.h"

/**
 * @brief Find the existing `SHLVL` entry inside the environment array.
 * @param heap_env Heap-owned environment array.
 * @return Matching index, or -1 when `SHLVL` is absent.
 */
static int	find_shlvl_index(char **heap_env)
{
	size_t	i;

	i = 0;
	while (heap_env[i])
	{
		if (ft_strncmp(heap_env[i], "SHLVL=", 6) == 0)
			return ((int)i);
		i++;
	}
	return (-1);
}

/**
 * @brief Compute the next shell level value from the inherited one.
 * @param existing_shlvl Parsed numeric value of the current `SHLVL`.
 * @return Next shell level, wrapped to 1 when the value grows too large.
 * BASH POSIX: Negative levels are reset to 0 before incrementing
 * BASH POSIX: Values >= 1000 reset to 1 with a warning
 */
static int	calculate_shlvl(int existing_shlvl)
{
	int	shlvl;

	if (existing_shlvl < 0)
		return (0);
	shlvl = existing_shlvl + 1;
	if (shlvl >= 1000)
	{
		ft_puterror("shell level (%d) too high, resetting to 1\n", shlvl);
		shlvl = 1;
	}
	return (shlvl);
}

/**
 * @brief Build the `SHLVL=` environment entry for a numeric level.
 * @param shlvl Shell level that must be serialized.
 * @return Newly allocated `SHLVL=<n>` string, or NULL on failure.
 */
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

/**
 * @brief Install the computed `SHLVL` entry into the environment array.
 * @param heap_env Heap-owned environment array being updated.
 * @param idx Existing `SHLVL` slot, or -1 when one must be appended.
 * @param shlvl Shell level value that must be stored.
 * @return This function does not return a value.
 */
static void	set_shlvl_entry(char **heap_env, int idx, int shlvl)
{
	char	*entry;
	size_t	j;

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
		j = 0;
		while (heap_env[j])
			j++;
		heap_env[j] = entry;
		heap_env[j + 1] = NULL;
	}
}

/**
 * @brief Ensure the shell environment contains an incremented `SHLVL`.
 * @param heap_env Heap-owned environment array initialized for the shell.
 * @return This function does not return a value.
 */
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
