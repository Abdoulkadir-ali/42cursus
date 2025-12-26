/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/26 16:28:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_algorithm_info(t_layout *l, t_gui *gui)
{
	if (gui->render_config->render_mode == RENDER_LINES)
		gui_layout_key_value(l, "Algorithm:", "Lines");
}
