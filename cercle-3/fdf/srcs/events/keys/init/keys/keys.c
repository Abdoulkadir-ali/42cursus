/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 11:44:51 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 19:07:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

void	set_key_actions(t_key_maps *key_maps)
{
	set_key_actions_1(key_maps);
	set_key_actions_2(key_maps);
	set_key_actions_3(key_maps);
	set_key_actions_4(key_maps);
	set_key_actions_5(key_maps);
}
