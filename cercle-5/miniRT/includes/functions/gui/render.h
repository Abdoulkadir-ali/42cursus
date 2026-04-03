/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:31:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_RENDER_H
# define GUI_RENDER_H

# include "physics.h"
# include "raytracing.h"
# include "input.h"
# include "mlx.h"
# include "types.h"
# include <pthread.h>
# include <sys/time.h>

# define TILE_SIZE 32
# define FONT_PATH "maps/font/font8.font"

int				gui_update(t_gui *gui);
t_gui			*gui_init(t_scene *scene, void *mlx);
void			gui_destroy(t_gui *gui);
bool			init_window(t_gui *gui);
void			init_camera(t_gui *gui);
void			gui_init_physics(t_gui *gui);
void			gui_init_render(t_gui *gui);
void			gui_render(t_gui *gui);
unsigned int	color_blend(unsigned int dst, int src, float alpha);
void			render_tiles(t_render *render);
void			render_tile(t_render *render, size_t id);
void			gui_update_hover(t_gui *gui);
void			process_pixel(t_render *render, t_vec2i pos, char *pixel_addr);
void			upscale_image(t_gui *gui);
void			fullres_toggle(t_gui *gui);
void			poll_map_job(t_gui *gui);
void			clear_selection(t_gui *gui);
double			update_delta(t_gui *gui);
void			update_animations(t_gui *gui, double dt);
void			update_physics_step(t_gui *gui, double dt);
void			update_autorefresh(t_gui *gui);
void			update_ambient(t_gui *gui);
const char		*mesh_name(t_mesh *mesh);
void			draw_char(t_gui *gui, unsigned char c, t_vec2i pos,
					unsigned int color);
int				panel_color(t_panel panel, t_vec2i pos);
void			draw_ui_help(t_gui *gui, int *y);
void			draw_ui_status(t_gui *gui, int *y);
void			draw_ui_object(t_gui *gui);
void			widget_draw_all(t_gui *gui);
void			draw_scene_panel_bg(t_gui *gui);
void			draw_inspector_bg(t_gui *gui);
bool			font_load(t_gui *gui, const char *path);

#endif
