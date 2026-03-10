/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:17:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:36:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

/**
 * @brief Initialize gradient vectors and the base permutation table.
 * @param state Noise state to initialize.
 */
static void	init_gradients(t_noise_state *state)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		state->grads[i].x = cos(i * 2.0 * M_PI / 256.0);
		state->grads[i].y = sin(i * 2.0 * M_PI / 256.0);
		state->perm[i] = i;
		i++;
	}
}

/**
 * @brief Shuffle the permutation table using the provided seed.
 * @param state Noise state whose permutation table is updated.
 * @param seed Seed used for deterministic shuffling.
 */
static void	init_permutation(t_noise_state *state, int seed)
{
	int						i;
	int						j;
	int						tmp;
	unsigned long long		next;

	next = 1;
	if (seed != 0)
		next = seed;
	i = 0;
	while (i < 256)
	{
		next = next * 6364136223846793005ULL + 1;
		j = (next >> 32) % 256;
		tmp = state->perm[i];
		state->perm[i] = state->perm[j];
		state->perm[j] = tmp;
		i++;
	}
	i = 0;
	while (i < 256)
	{
		state->perm[256 + i] = state->perm[i];
		i++;
	}
}

/**
 * @brief Allocate and initialize a Perlin noise state.
 * @param seed Seed used to randomize the permutation table.
 * @return Allocated noise state, or `NULL` on failure.
 */
t_noise_state	*init_noise(int seed)
{
	t_noise_state	*state;

	state = ft_calloc(1, sizeof(t_noise_state));
	if (!state)
		return (NULL);
	init_gradients(state);
	init_permutation(state, seed);
	return (state);
}
