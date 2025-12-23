/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:44 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/23 18:41:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	display_algorithm_info(t_layout *l, t_gui *gui)
{
	if (gui->render_config->render_mode == RENDER_LINES)
		gui_layout_key_value(l, "Algorithm (K):", "Lines");
	else
		gui_layout_key_value(l, "Algorithm (K):", "Triangles");
	if (gui->render_config->filled)
		gui_layout_key_value(l, "Filled (G):", "Yes");
	else
		gui_layout_key_value(l, "Filled (G):", "No");
}
