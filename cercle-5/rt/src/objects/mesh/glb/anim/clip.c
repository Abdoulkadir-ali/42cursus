/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/30 00:32:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glb.h"
#include "io.h"
#include "skeletal.h"

typedef struct s_sampler
{
	int	input_acc;
	int	output_acc;
	int	interp;
}				t_sampler;

static int	parse_path(const char *p, const char *end)
{
	if (!p)
		return (-1);
	if (json_streq(p, end, "translation"))
		return (0);
	if (json_streq(p, end, "rotation"))
		return (1);
	if (json_streq(p, end, "scale"))
		return (2);
	return (-1);
}

static int	parse_interp(const char *p, const char *end)
{
	if (!p)
		return (0);
	if (json_streq(p, end, "STEP"))
		return (1);
	if (json_streq(p, end, "CUBICSPLINE"))
		return (2);
	return (0);
}

static void	read_sampler(const t_glb *g, const char *samplers, int idx,
		t_sampler *out)
{
	const char	*s;
	const char	*v;

	out->input_acc = -1;
	out->output_acc = -1;
	out->interp = 0;
	s = json_arr_get(samplers, g->jend, idx);
	if (!s)
		return ;
	v = json_obj_find(s, g->jend, "input");
	if (v)
		out->input_acc = (int)json_int(v, g->jend);
	v = json_obj_find(s, g->jend, "output");
	if (v)
		out->output_acc = (int)json_int(v, g->jend);
	v = json_obj_find(s, g->jend, "interpolation");
	out->interp = parse_interp(v, g->jend);
}

static void	decimate_cubic(t_anim_chan *ch)
{
	float	*nv;
	int		comp;
	int		i;
	int		j;

	if (ch->n_keys <= 0 || !ch->values)
		return ;
	comp = ch->comp;
	nv = (float *)malloc(sizeof(float) * comp * ch->n_keys);
	if (!nv)
		return ;
	i = -1;
	while (++i < ch->n_keys)
	{
		j = -1;
		while (++j < comp)
			nv[i * comp + j] = ch->values[i * 3 * comp + comp + j];
	}
	free(ch->values);
	ch->values = nv;
}

static int	build_chan(t_glb *g, const char *samplers, const char *chan,
		t_anim_chan *out)
{
	const char	*tgt;
	const char	*v;
	t_sampler	sm;
	int			cnt;
	int			ne;

	memset(out, 0, sizeof(*out));
	out->target_node = -1;
	tgt = json_obj_find(chan, g->jend, "target");
	if (!tgt)
		return (-1);
	v = json_obj_find(tgt, g->jend, "node");
	if (v)
		out->target_node = (int)json_int(v, g->jend);
	out->path = parse_path(json_obj_find(tgt, g->jend, "path"), g->jend);
	if (out->target_node < 0 || out->path < 0)
		return (-1);
	v = json_obj_find(chan, g->jend, "sampler");
	if (!v)
		return (-1);
	read_sampler(g, samplers, (int)json_int(v, g->jend), &sm);
	out->interp = sm.interp;
	out->times = glb_read_float(g, sm.input_acc, &out->n_keys, &ne);
	if (!out->times)
		return (-1);
	out->values = glb_read_float(g, sm.output_acc, &cnt, &out->comp);
	if (!out->values)
		return (free(out->times), out->times = NULL, -1);
	if (sm.interp == 2)
		decimate_cubic(out);
	return (0);
}

static void	build_clip(t_glb *g, const char *anim, t_anim_clip *clip)
{
	const char	*v;
	const char	*chans;
	const char	*samplers;
	int			n;
	int			i;
	float		last;

	memset(clip, 0, sizeof(*clip));
	v = json_obj_find(anim, g->jend, "name");
	if (v)
		json_str_copy(v, g->jend, clip->name, sizeof(clip->name));
	chans = json_obj_find(anim, g->jend, "channels");
	samplers = json_obj_find(anim, g->jend, "samplers");
	if (!chans || !samplers)
		return ;
	n = json_arr_len(chans, g->jend);
	if (n <= 0)
		return ;
	clip->chans = (t_anim_chan *)calloc(n, sizeof(t_anim_chan));
	if (!clip->chans)
		return ;
	i = -1;
	while (++i < n)
	{
		if (build_chan(g, samplers, json_arr_get(chans, g->jend, i),
				&clip->chans[clip->n_chans]) == 0)
		{
			last = clip->chans[clip->n_chans].times[
				clip->chans[clip->n_chans].n_keys - 1];
			if (last > clip->duration)
				clip->duration = last;
			clip->n_chans++;
		}
	}
}

void	glb_capture_clips(t_glb *g)
{
	const char	*anims;
	t_animator	*a;
	int			i;

	a = g->anim;
	anims = json_obj_find(g->json, g->jend, "animations");
	if (!anims)
		return ;
	a->n_clips = json_arr_len(anims, g->jend);
	if (a->n_clips <= 0)
	{
		a->n_clips = 0;
		return ;
	}
	a->clips = (t_anim_clip *)calloc(a->n_clips, sizeof(t_anim_clip));
	if (!a->clips)
	{
		a->n_clips = 0;
		return ;
	}
	i = -1;
	while (++i < a->n_clips)
		build_clip(g, json_arr_get(anims, g->jend, i), &a->clips[i]);
}
