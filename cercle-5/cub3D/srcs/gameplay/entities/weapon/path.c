/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_weapon_anim_paths.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 22:58:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/25 23:19:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine.h"

void	anim_set_paths(t_anim *anim, t_anim_paths paths)
{
	if (!anim)
		return ;
	anim->paths = paths;
}
