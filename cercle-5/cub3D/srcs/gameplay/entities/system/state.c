/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 16:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/27 22:41:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"

void	set_state(t_entity *ent, t_entity_state new_state, t_anim_clip *clip)
{
	if (ent->state == new_state)
		return ;
	ent->state = new_state;
	ent->clip = clip;
	ent->anim.frame = 0;
	ent->anim.timer_us = 0;
}
