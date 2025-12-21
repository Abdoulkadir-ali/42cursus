/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:51:12 by abdoali           #+#    #+#             */
/*   Updated: 2025/12/21 00:23:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_H
# define WINDOW_H

typedef struct s_image
{
	void				*img;
	char				*img_addr;
	size_t				img_bpp;
	size_t				img_line_len;
	int					img_endian;
}						t_image;

typedef struct s_window
{
	void				*mlx_ptr;
	void				*ptr;
	size_t				width;
	size_t				height;

	t_image				main_img;
	t_image				gui_img;
	float				*z_buffer;
}						t_window;

typedef struct s_mlx_win_list
{
	void				*window;
	void				*gc;
}						t_mlx_win_list;

typedef struct s_mlx_ptr
{
	void				*display;
}						t_mlx_ptr;

typedef struct s_data	t_data;

t_window				*init_window(void *mlx_ptr);
int						init_window_main_image(t_window *win, void *mlx);
int						init_window_system(t_data *data);

#endif