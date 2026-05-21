/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 04:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 03:26:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "skeletal.h"

static void	free_clips(t_animator *a)
{
	int	i;
	int	j;

	i = -1;
	while (++i < a->n_clips)
	{
		j = -1;
		while (++j < a->clips[i].n_chans)
		{
			free(a->clips[i].chans[j].times);
			free(a->clips[i].chans[j].values);
		}
		free(a->clips[i].chans);
	}
	free(a->clips);
}

static void	free_prims(t_animator *a)
{
	int	i;

	i = -1;
	while (++i < a->n_prims)
	{
		free(a->prims[i].positions);
		free(a->prims[i].uvs);
		free(a->prims[i].weights);
		free(a->prims[i].joints);
		free(a->prims[i].indices);
	}
	free(a->prims);
}

static void	free_skins(t_animator *a)
{
	int	i;

	i = -1;
	while (++i < a->n_skins)
	{
		free(a->skins[i].joints);
		free(a->skins[i].ibm);
	}
	free(a->skins);
}

void	skel_animator_destroy(t_animator *a)
{
	if (!a)
		return ;
	free_clips(a);
	free_prims(a);
	free_skins(a);
	free(a->nodes);
	free(a->joint_mats);
	free(a);
}
