/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 18:02:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/07 02:40:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMATION_H
# define ANIMATION_H

# include "map.h"
# include "maths.h"
# include "window.h"

# define WPN_W 64
# define WPN_SCALE 4
# define WPN_MIN_W 64
# define WPN_MIN_H 64
# define WPN_MAX_FRAMES 256
# define DESIRED_HEIGHT 1000

/* Transparent colour-key (R=255, G=0, B=255) */
# define WPIX_TRANS 0xFF00FFu

typedef struct s_world		t_world;
typedef struct s_app		t_app;

typedef struct s_render_params
{
	struct s_window			*win;
	unsigned int			*buf;
	t_vec2s					src;
	t_vec2s					dst;
	t_vec2i					offset;
}							t_render_params;

typedef struct s_anim_state
{
	size_t					frame;
	size_t					frame_count;
	int						ticks;
	int						tick_delay;
	int						timer_us;
	int						loop;
	int						playing;
}							t_anim_state;

typedef struct s_anim_clip
{
	unsigned int			**frames;
	size_t					frame_count;
	size_t					frame_capacity;
	t_vec2s					size;
	t_vec2s					offset;
	int						original_fps;
	int						frame_duration_us;
}							t_anim_clip;

typedef struct s_anim_paths
{
	const char				*idle;
	const char				*walking;
	const char				*sprint;
	const char				*shooting;
	const char				*reload;
}							t_anim_paths;

typedef struct s_anim_clips
{
	t_anim_clip				*idle;
	t_anim_clip				*walking;
	t_anim_clip				*sprint;
	t_anim_clip				*shooting;
	t_anim_clip				*reload;
}							t_anim_clips;
typedef struct s_anim_params
{
	int						fire;
	int						reload;
	int						move;
	int						sprint;
	float					move_scale;
	float					attack_scale;
}							t_anim_params;

typedef struct s_anim
{
	t_anim_clips			clips;
	t_anim_paths			paths;
	t_anim_state			state;
	int						weapon_type;
	int						firing;
	int						reloading;
	int						moving;
	int						sprinting;
	t_anim_clip				*active_clip;
	t_texture				punch_texture;
	float					bob_phase;
}							t_anim;

/* Aliases for backward compatibility if needed */
typedef t_anim				t_weapon_anim;
typedef t_anim_clip			t_weapon_clip;

typedef struct s_cached_clip
{
	char					*path;
	t_anim_clip				clip;
	struct s_cached_clip	*next;
}							t_cached_clip;

typedef struct s_anim_mgr
{
	t_cached_clip			*cache;
}							t_anim_mgr;

/* Public API */
void						anim_init(t_anim *wa, struct s_window *win,
								struct s_world *world);
void						anim_set_paths(t_anim *wa, t_anim_paths paths);
void						init_pistol(t_anim *wa, struct s_window *win,
								struct s_world *world);
int							load_anim_clip(t_anim_clip *clip,
								struct s_window *win, const char *path,
								struct s_world *world);
t_anim_clip					*anim_get_cached_clip(struct s_world *world,
								struct s_window *win, const char *path,
								struct s_app *app);
void						tick_weapon_anim(t_anim *wa, t_anim_params p,
								int elapsed_us);
void						render_weapon_sprite(struct s_window *win,
								t_anim *wa);
void						anim_free(t_anim *wa);
void						anim_mgr_free(struct s_world *world);

/* Internal Helpers */
char						*anim_get_dirname(const char *path);
char						*anim_join_path(const char *dir, const char *file);

int							anim_init_clip(t_anim_clip *clip);
void						anim_free_clip(t_anim_clip *clip);
int							anim_alloc_clips(t_anim *wa);
void						anim_free_clips(t_anim *wa);

t_anim_clip					*anim_get_active_clip(t_anim *wa);
void						anim_set_active_clip(t_anim *wa, t_anim_clip *clip,
								int delay, int loop);

t_vec3						anim_decode_pixel(unsigned int p);
int							anim_is_transparent(unsigned int pix);
void						anim_blend_pixel(struct s_window *win, t_vec2i pos,
								unsigned int src_pix);
void						anim_write_pixel(struct s_window *win, t_vec2i pos,
								unsigned int src_pix);
void						anim_render_scaled(t_render_params *p);
void						anim_render_hud(struct s_window *win,
								t_texture *tex);

int							parse_anim_config(char *line, char *token,
								int *count);
int							anim_grow_clip_capacity(t_anim_clip *clip,
								size_t min_capacity);
int							parse_meta(t_anim_clip *clip, char *line);

#endif
