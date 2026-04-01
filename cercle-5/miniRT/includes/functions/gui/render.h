/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:00:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 17:20:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_RENDER_H
# define GUI_RENDER_H

# include "input.h"
# include "editor.h"
# include "map.h"
# include "physics.h"
# include "raytracing.h"
# include "mesh.h"
# include "profiler.h"
# include "t_render.h"

# define TILE_SIZE 32

/* Prototypes */
void			gui_render(struct s_gui *gui);
unsigned int	color_blend(unsigned int dst, int src, float alpha);
void			render_tiles(t_render *render);
bool			update_hover(struct s_gui *gui, t_render *render);
void			process_pixel(t_render *render, t_vec2i pos, char *pixel_addr);
void			make_camera_ray(t_render *render, double x, double y, t_ray *ray);
void			upscale_image(struct s_gui *gui);
void			fullres_toggle(struct s_gui *gui);

/* Render loop */
void			poll_map_job(t_gui *gui);
double			update_delta(t_gui *gui);
void			update_animations(t_gui *gui, double delta);
void			update_physics_step(t_gui *gui, double delta);
void			update_autorefresh(t_gui *gui);
void			update_ambient(t_gui *gui);

/* Overlay internals */
const char		*mesh_name(t_mesh *mesh);
void			draw_char(t_gui *gui, unsigned char c, int x, int y,
				unsigned int color);
int				panel_color(t_panel panel, int i, int j);

#endif
