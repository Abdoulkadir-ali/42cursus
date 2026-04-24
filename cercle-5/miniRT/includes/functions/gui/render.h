/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 19:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_RENDER_H
# define GUI_RENDER_H

# include "input.h"
# include "mlx.h"
# include "physics.h"
# include "raytracing.h"
# include "animations.h"
# include "types.h"
# include "optimizations.h"
# include "settings.h"
# include <pthread.h>
# include <sys/time.h>
#include <stdatomic.h>

# define DEPTH_THRESH 0.15f
# define TILE_SIZE 32
# define FONT_PATH "maps/font/font8.font"




int				gui_update(t_gui *gui);
t_gui			*gui_init(t_scene *scene, void *mlx);
void			gui_destroy(t_gui *gui);
bool			init_window(t_gui *gui);
void			init_camera(t_gui *gui);
void			gui_init_physics(t_gui *gui);
void			gui_init_anim(t_gui *gui);
void			gui_init_render(t_gui *gui);
void			gui_render(t_gui *gui);
unsigned int	color_blend(unsigned int dst, int src, float alpha);
void			render_tiles_worker(t_render *render);
void			render_tile(t_render *render, size_t id);
void			gui_update_hover(t_gui *gui);
void			gui_parallel_task_worker(t_gui *gui, t_pool_task type);
void			*gui_worker(void *ptr);
void			process_pixel(t_render *render, t_vec2i pos, char *pixel_addr);
void			upscale_image(t_gui *gui);
void			upscale_band(t_gui *gui, size_t y_start, size_t y_end);
void			upscale_pixel(t_gui *gui, t_vec2i dst, t_vec2 src);
void			smooth_render_band(t_gui *gui, size_t y_start, size_t y_end);
void			smooth_render(t_gui *gui);
void			fullres_toggle(t_gui *gui);
void			poll_map_job(t_gui *gui);
void			clear_selection(t_gui *gui);
double			update_delta(t_gui *gui);
void			anim_step(t_gui *gui, double delta);
void			physics_step(t_gui *gui, double delta);
void			scene_swap_step(t_gui *gui);
void			bvh_step(t_gui *gui);
void			raytrace_step(t_gui *gui, double delta);
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
void			draw_ui_orient(t_gui *gui);
void			draw_ui_pixels(t_gui *gui);
void			draw_ui_strings(t_gui *gui, t_camera_controller *ctrl);
bool			font_load(t_gui *gui, const char *path);
void			*gui_worker(void *ptr);



t_vec3i				rt_unpack_color_v(size_t c);
size_t				rt_pack_color_v(t_vec3i v);
void					apply_bcg(t_vec3f *ch, const t_raytracer_settings *opts);
/* ---- inline color helpers: avoid double round-trip ---- */
static inline __attribute__((always_inline))
t_vec3f	rt_unpack_color(size_t c)
{
	return ((t_vec3f){
		(float)((c >> 16) & 0xFF),
		(float)((c >> 8) & 0xFF),
		(float)(c & 0xFF),
		0.0f});
}

static inline __attribute__((always_inline))
size_t	rt_pack_color(t_vec3f v)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	r = (uint32_t)(v.x < 0.0f ? 0.0f : v.x > 255.0f ? 255.0f : v.x);
	g = (uint32_t)(v.y < 0.0f ? 0.0f : v.y > 255.0f ? 255.0f : v.y);
	b = (uint32_t)(v.z < 0.0f ? 0.0f : v.z > 255.0f ? 255.0f : v.z);
	return ((size_t)((r << 16) | (g << 8) | b));
}

static inline __attribute__((always_inline))
size_t	bilerp_pixel(size_t c[4], t_vec4f w)
{
	float		wt;
	t_vec3f	acc;
	size_t	i;
	t_vec3f	rgb;
	float		*wf;

	wf = (float *)&w;
	wt = wf[0] + wf[1] + wf[2] + wf[3];
	if (wt < 1e-6f)
		return (c[0]);
	acc = (t_vec3f){0, 0, 0, 0};
	i = 0;
	while (i < 4)
	{
		rgb = rt_unpack_color(c[i]);
		acc.x += rgb.x * wf[i];
		acc.y += rgb.y * wf[i];
		acc.z += rgb.z * wf[i];
		i++;
	}
	{
		const float	rcp_wt = 1.0f / wt;
		acc.x *= rcp_wt;
		acc.y *= rcp_wt;
		acc.z *= rcp_wt;
	}
	return (rt_pack_color(acc));
}

static inline __attribute__((always_inline))
void	get_weights(t_vec4f *w, t_vec2f f, float *db[2])
{
	float	d00;
	float	*wf;

	wf = (float *)w;
	wf[0] = (1.0f - f.x) * (1.0f - f.y);
	wf[1] = f.x * (1.0f - f.y);
	wf[2] = (1.0f - f.x) * f.y;
	wf[3] = f.x * f.y;
	if (db[0])
	{
		d00 = db[0][0];
		if (d00 > 1e-4f)
		{
			const float	thresh_abs = DEPTH_THRESH * d00;
			if (__builtin_fabsf(db[0][1] - d00) > thresh_abs)
				wf[1] = 0.0f;
			if (__builtin_fabsf(db[1][0] - d00) > thresh_abs)
				wf[2] = 0.0f;
			if (__builtin_fabsf(db[1][1] - d00) > thresh_abs)
				wf[3] = 0.0f;
		}
	}
}

#endif
