/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:41:27 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 22:35:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H


typedef struct s_data	t_data;

int		mouse_press(int button, int x, int y, t_data *data);
int		mouse_release(int button, int x, int y, t_data *data);
int		mouse_move(int x, int y, t_data *data);

int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);

int		loop_hook(t_data *data);


void	process_movement(t_data *data);

/* ========== KEY HANDLERS ========== */
void	cycle_projection(t_data *data);
void	reset_view(t_data *data);
void	adjust_move_speed(t_data *data, int increase);

// Cleanup and exit
int		cleanup_and_exit(t_data *data);

#endif
