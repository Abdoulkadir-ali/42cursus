/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   releases.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:46:03 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/25 21:51:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	set_key_releases(t_key_maps *key_maps)
{
	key_maps->key_releases[XK_Up] = handle_release_flag;
	key_maps->key_releases[XK_Down] = handle_release_flag;
	key_maps->key_releases[XK_Left] = handle_release_flag;
	key_maps->key_releases[XK_Right] = handle_release_flag;
	key_maps->key_releases[XK_Control_L] = handle_release_flag;
	key_maps->key_releases[XK_Control_R] = handle_release_flag;
	key_maps->key_releases[XK_Shift_L] = handle_release_flag;
	key_maps->key_releases[XK_Shift_R] = handle_release_flag;
	key_maps->key_releases[XK_l] = handle_release_flag;
	key_maps->key_releases[XK_L] = handle_release_flag;
	key_maps->key_releases[XK_z] = handle_release_flag;
	key_maps->key_releases[XK_Z] = handle_release_flag;
	key_maps->key_releases[XK_f] = handle_release_flag;
	key_maps->key_releases[XK_F] = handle_release_flag;
	key_maps->key_releases[XK_d] = handle_release_flag;
	key_maps->key_releases[XK_D] = handle_release_flag;
	key_maps->key_releases[XK_h] = handle_release_flag;
	key_maps->key_releases[XK_H] = handle_release_flag;
	key_maps->key_releases[XK_t] = handle_release_flag;
	key_maps->key_releases[XK_T] = handle_release_flag;
	key_maps->key_releases[XK_a] = handle_release_flag;
	key_maps->key_releases[XK_A] = handle_release_flag;
}
