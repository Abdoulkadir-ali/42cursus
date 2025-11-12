/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 21:09:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

# include "camera.h"

typedef struct s_image
{
	void		*img;
	char		*img_addr;
	int			img_bpp;
	int			img_line_len;
	int			img_endian;
}				t_image;

typedef struct s_window
{
	void		*mlx_ptr;
	void		*ptr;
	int			width;
	int			height;

	t_image		main_img;
	t_image		gui_img;
	float		*z_buffer;
}				t_window;

t_window		init_window(void *mlx_ptr);

#endif