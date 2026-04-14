/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   jiggle.c                                          :+:    :+:            */
/*                                                   +:+                     */
/*   By: abdoali <abdoali@student.42.fr>            +#+                      */
/*                                                 +#+                       */
/*   Created: 2026/04/12 00:00:00 by abdoali       #+#    #+#                */
/*   Updated: 2026/04/12 00:00:00 by abdoali      ###   ########.fr          */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "physics.h"

/*
** J key — fires a random upward impulse on every active unfixed soft-body
** particle so the spheres visibly bounce and jiggle.
*/
void	soft_body_jiggle_press(t_gui *gui)
{
	if (!gui->scene || !gui->physics_enabled)
		return ;
	soft_body_jiggle(gui->scene);
}
