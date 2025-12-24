/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 02:15:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:22:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generator.h"

static void	compute_corner_hashes(t_noise_state *state,
			t_vec2 int_pos, t_vec3 *h1, t_vec3 *h2)
{
	h1->x = state->perm[int_pos.x] + int_pos.y;
	h1->y = state->perm[h1->x];
	h1->z = state->perm[h1->x + 1];
	h2->x = state->perm[int_pos.x + 1] + int_pos.y;
	h2->y = state->perm[h2->x];
	h2->z = state->perm[h2->x + 1];
}

static float	interpolate_gradients(t_noise_state *state,
			t_vec3 h1, t_vec3 h2, t_interp_params params)
{
	t_vec2d	grad_col1;
	t_vec2d	grad_col2;
	t_vec2d	inner;

	grad_col1.x = grad(state, state->perm[h1.y], params.x, params.y);
	grad_col1.y = grad(state, state->perm[h1.z], params.x, params.y - 1);
	grad_col2.x = grad(state, state->perm[h2.y], params.x - 1, params.y);
	grad_col2.y = grad(state, state->perm[h2.z],
			params.x - 1, params.y - 1);
	inner = lerp_vec(params.fade_vals.x, grad_col1, grad_col2);
	return (lerp(params.fade_vals.y, inner.x, inner.y));
}

float	noise_at(t_noise_state *state, float x, float y)
{
	t_vec2			int_pos;
	t_interp_params	params;
	t_vec3			corner_hashes1;
	t_vec3			corner_hashes2;

	int_pos.x = (int)floor(x) & 255;
	int_pos.y = (int)floor(y) & 255;
	x -= floor(x);
	y -= floor(y);
	params.fade_vals.x = fade(x);
	params.fade_vals.y = fade(y);
	params.x = x;
	params.y = y;
	compute_corner_hashes(state, int_pos, &corner_hashes1, &corner_hashes2);
	return (interpolate_gradients(state,
			corner_hashes1, corner_hashes2, params));
}

float	perlin2d(t_noise_state *state, t_vec2d pos)
{
	return (noise_at(state, pos.x, pos.y));
}
