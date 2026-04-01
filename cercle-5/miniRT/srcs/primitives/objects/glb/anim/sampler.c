/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 16:37:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/30 22:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"

static void	load_sampler_outputs(t_json_value *json, char *bin,
				t_anim_sampler *s, int out_idx)
{
	t_accessor		acc;
	t_buffer_view	bv;
	t_json_value	*acc_json;
	const char		*type_str;
	int				num;

	glb_parse_accessor(json, out_idx, &acc);
	s->outputs = malloc(sizeof(float) * 4 * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	acc_json = json_at(json_get(json, "accessors"), out_idx);
	type_str = json_as_string(json_get(acc_json, "type"));
	num = 3;
	if (type_str && !strcmp(type_str, "VEC4"))
		num = 4;
	if (type_str && !strcmp(type_str, "SCALAR"))
		num = 1;
	glb_extract_data((t_extract){bin, &acc, &bv, s->outputs,
		sizeof(float) * num, sizeof(float) * num,
		sizeof(float) * num, s->count});
}

/**
 * Loads a GLB animation sampler's input (timestamps) and output (keyframe data)
 * from the provided JSON and binary buffer.
 */
void	load_glb_sampler(t_json_value *json, char *bin, t_anim_sampler *s,
			t_json_value *s_json)
{
	t_accessor		acc;
	t_buffer_view	bv;
	const char		*interp;

	interp = json_as_string(json_get(s_json, "interpolation"));
	glb_parse_accessor(json, json_get_int(s_json, "input"), &acc);
	s->count = acc.count;
	if (s->count <= 0)
		return ;
	s->inputs = malloc(sizeof(float) * s->count);
	glb_parse_buffer_view(json, acc.buffer_view, &bv);
	glb_extract_data((t_extract){bin, &acc, &bv, s->inputs, sizeof(float),
		sizeof(float), sizeof(float), s->count});
	load_sampler_outputs(json, bin, s, json_get_int(s_json, "output"));
	s->method = INTERP_LINEAR;
	if (interp && !strcmp(interp, "STEP"))
		s->method = INTERP_STEP;
	else if (interp && !strcmp(interp, "CUBICSPLINE"))
		s->method = INTERP_CUBIC;
}
