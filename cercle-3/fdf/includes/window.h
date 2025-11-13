/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/13 15:39:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

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

typedef struct s_data	t_data;

t_window		*init_window(void *mlx_ptr);
int				init_window_main_image(t_window *win, void *mlx);
int				init_window_system(t_data *data);

#endif