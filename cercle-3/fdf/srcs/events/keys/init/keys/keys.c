/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:44:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 03:23:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

/**
 * @brief Populate the key press action table.
 * @param key_maps Key-map structure to update.
 */
void	set_key_actions(t_key_maps *key_maps)
{
	set_key_actions_1(key_maps);
	set_key_actions_2(key_maps);
	set_key_actions_3(key_maps);
	set_key_actions_4(key_maps);
	set_key_actions_5(key_maps);
}
