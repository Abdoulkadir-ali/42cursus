/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 23:55:00 by antigravity       #+#    #+#             */
/*   Updated: 2025/12/23 23:55:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

static int		g_perm[512];
static t_vec2d	g_grads[256];
static int		g_initialized = 0;

static float	fade(float t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

static float	lerp(float t, float a, float b)
{
	return (a + t * (b - a));
}

static float	grad(int hash, float x, float y)
{
	int		h;
	t_vec2d	g;

	h = hash & 255;
	g = g_grads[h];
	return (g.x * x + g.y * y);
}

void	init_noise(int seed)
{
	int	i;
	int	j;
	int	tmp;

	if (g_initialized && seed == 0)
		return ;
	// Simple seed usage (not cryptographic)
	// If seed is 0, we can use time or just keep default if already init
	// But required behavior might be re-seeding
	// Let's implement a basic shuffle
	
	// Initialize gradients
	i = 0;
	while (i < 256)
	{
		g_grads[i].x = cos(i * 2.0 * M_PI / 256.0);
		g_grads[i].y = sin(i * 2.0 * M_PI / 256.0);
		g_perm[i] = i;
		i++;
	}
	
	// Shuffle permutation
	// A simple LCG or just a loop with seed
	// For simplicity in this env without srand/rand, we implement a custom shuffle
	// or rely on a simple hash if we want determinism with seed
	
	// Using a simple congruent generator for shuffle
	unsigned long long next = 1;
	if (seed != 0)
		next = seed;
	
	i = 0;
	while (i < 256)
	{
		next = next * 6364136223846793005ULL + 1;
		j = (next >> 32) % 256;
		tmp = g_perm[i];
		g_perm[i] = g_perm[j];
		g_perm[j] = tmp;
		i++;
	}

	i = 0;
	while (i < 256)
	{
		g_perm[256 + i] = g_perm[i];
		i++;
	}
	g_initialized = 1;
}

float	noise_at(float x, float y)
{
	int		X;
	int		Y;
	float	u;
	float	v;
	int		A;
	int		aa;
	int		ab;
	int		B;
	int		ba;
	int		bb;

	if (!g_initialized)
		init_noise(12345);

	X = (int)floor(x) & 255;
	Y = (int)floor(y) & 255;
	x -= floor(x);
	y -= floor(y);
	u = fade(x);
	v = fade(y);

	A = g_perm[X] + Y;
	aa = g_perm[A];
	ab = g_perm[A + 1];
	B = g_perm[X + 1] + Y;
	ba = g_perm[B];
	bb = g_perm[B + 1];

	return (lerp(v, lerp(u, grad(g_perm[aa], x, y),
				grad(g_perm[ba], x - 1, y)),
			lerp(u, grad(g_perm[ab], x, y - 1),
				grad(g_perm[bb], x - 1, y - 1))));
}

float	perlin2d(float x, float y, float freq, int depth)
{
	(void)freq;
	(void)depth;
	// Let's stick to single octave here for flexibility, builder handles octaves.
	
	return (noise_at(x, y));
}
