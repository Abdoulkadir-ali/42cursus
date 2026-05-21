/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 17:25:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# include "input.h"
# include "io.h"
# include "maths.h"
# include "parsing.h"
# include "physics.h"
# include "raytracing.h"
# include "render.h"
# include "scene.h"
# include "ui.h"
# include "utils.h"
# include "window.h"
# include "libft.h"
# include "skeletal.h"

typedef struct s_settings
{
	t_raytracing_settings	rt;
	t_render_settings			render;
	t_physics_settings		physics;
	t_animation_settings	anim;
	t_controls_settings		controls;
}			t_settings;

typedef struct s_timing
{
	double	last_render_ms;
	double	frame_dt;
	double	last_t;
	int		frames;
	double	fps_acc;
	double	fps;
}			t_timing;

typedef struct s_app
{
	void			*mlx;
	void			*win;
	t_image			img;
	t_scene			scene;
	t_bvh			bvh;
	t_thread_pool	pool;
	t_input			input;
	t_ui_state		ui;
	t_settings		set;
	t_pickbuf		pick;
	t_timing		time;
	t_phys_world	phys;
	int				win_w;
	int				win_h;
	int				render_w;
	int				render_h;
	int				dirty;
	int				running;
	int				selected;
	int				moving;
	float			*accum;
	float			*depth_buffer;
	float			*taa_scratch;
	int				accum_w;
	int				accum_h;
	int				accum_samples;
}					t_app;

# ifndef DEFAULT_FOV
#  define DEFAULT_FOV 70.0f
# endif
# ifndef MOUSE_SENS
#  define MOUSE_SENS 0.0035f
# endif
# ifndef MOVE_SPEED
#  define MOVE_SPEED 4.0f
# endif

int		mini_rt(int argc, char **argv, int bench);
int		usage(void);
int		app_init_subsystems(t_app *app, char *path);
void	settings_defaults(t_app *app);
void	run_bench(t_app *app, int samples);
int		ensure_default_texture(t_scene *s);

#endif
