/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skin.c                                             :+:      :+:    :+:   */
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

static void	read_joints(const t_glb *g, const char *skin, t_anim_skin *s)
{
	const char	*joints;
	const char	*el;
	int			j;

	joints = json_obj_find(skin, g->jend, "joints");
	s->n_joints = joints ? json_arr_len(joints, g->jend) : 0;
	if (s->n_joints <= 0)
	{
		s->joints = NULL;
		return ;
	}
	s->joints = (int *)calloc(s->n_joints, sizeof(int));
	if (!s->joints)
	{
		s->n_joints = 0;
		return ;
	}
	j = -1;
	while (++j < s->n_joints)
	{
		el = json_arr_get(joints, g->jend, j);
		s->joints[j] = (int)json_int(el, g->jend);
	}
}

static void	read_ibm(const t_glb *g, const char *skin, t_anim_skin *s)
{
	const char	*v;
	int			cnt;
	int			ne;
	int			j;

	s->ibm = NULL;
	v = json_obj_find(skin, g->jend, "inverseBindMatrices");
	if (v && s->n_joints > 0)
	{
		s->ibm = glb_read_float(g, (int)json_int(v, g->jend), &cnt, &ne);
		if (s->ibm && cnt >= s->n_joints && ne == 16)
			return ;
		free(s->ibm);
		s->ibm = NULL;
	}
	if (s->n_joints <= 0)
		return ;
	s->ibm = (float *)malloc(sizeof(float) * 16 * s->n_joints);
	if (!s->ibm)
		return ;
	j = -1;
	while (++j < s->n_joints)
		skel_m4_identity(&s->ibm[j * 16]);
}

void	glb_capture_skins(t_glb *g)
{
	const char	*skins;
	const char	*skin;
	t_animator	*a;
	int			i;

	a = g->anim;
	skins = json_obj_find(g->json, g->jend, "skins");
	if (!skins)
		return ;
	a->n_skins = json_arr_len(skins, g->jend);
	if (a->n_skins <= 0)
		return ;
	a->skins = (t_anim_skin *)calloc(a->n_skins, sizeof(t_anim_skin));
	if (!a->skins)
	{
		a->n_skins = 0;
		return ;
	}
	i = -1;
	while (++i < a->n_skins)
	{
		skin = json_arr_get(skins, g->jend, i);
		read_joints(g, skin, &a->skins[i]);
		read_ibm(g, skin, &a->skins[i]);
		if (a->skins[i].n_joints > a->max_joints)
			a->max_joints = a->skins[i].n_joints;
	}
	if (a->max_joints > 0)
		a->joint_mats = (float *)calloc(a->max_joints * 16, sizeof(float));
}
