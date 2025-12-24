/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/24 02:35:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

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
