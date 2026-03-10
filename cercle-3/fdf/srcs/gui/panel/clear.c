/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/10 01:51:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * @brief Clear the GUI image buffer before rebuilding the panel.
 * @param gui GUI object owning the window-side GUI image.
 */
void	clear_gui(t_gui *gui)
{
	int		total_bytes;
	char	*buffer;

	if (!gui->window->gui_img.img_addr)
		return ;
	total_bytes = gui->window->height * gui->window->gui_img.img_line_len;
	buffer = gui->window->gui_img.img_addr;
	ft_memset(buffer, 0, total_bytes);
}
