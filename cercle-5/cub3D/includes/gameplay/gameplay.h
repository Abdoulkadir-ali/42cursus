/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 03:34:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 03:28:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

/* UTILITIES */
# include "debug.h"
# include "error.h"
# include "exit.h"
# include "libft.h"

/* DEPENDENCIES */
# include "animation.h"
# include "map.h"
# include "tex_cache.h"
# include "window.h"
# include <stdint.h>

# define WEAPON_COUNT 3

# define MOUSE_SENSITIVITY 0.002f
# define PITCH_SENSITIVITY 0.002f
# define MAX_PITCH 1.5f
# define MOVE_MARGIN 0.2f
# define PI_F 3.1415926535f
# define PLAYER_VIEW_PLANE_SCALE 0.66f
# define PITCH_OFFSET_EPSILON 0.0001f
# define ENTITY_DEATH_LIFETIME_US 4000000
# define ITEM_LIFETIME_US 9000000

/* Vertical camera (jump / posZ) */
# define JUMP_IMPULSE 5.0f
# define GRAVITY_ACCEL 9.81f
# define MAX_POS_Z 0.7f
# define MIN_POS_Z -0.18f
# define WALL_HEIGHT 2.0f

/* Weapons */
# define MELEE_RANGE 1.6f
# define MELEE_CONE_DOT 0.7f
# define PROJECTILE_SPEED 8.0f
# define PROJECTILE_RADIUS 0.35f
# define PROJECTILE_DAMAGE 60
# define PROJECTILE_LIFETIME_US 4000000

typedef struct s_dda				t_dda;
typedef struct s_player				t_player;
typedef struct s_player_controller	t_player_controller;

typedef struct s_keymap_entry
{
	int								keycode;
	uint32_t						flag;
}									t_keymap_entry;

typedef struct s_actor
{
	t_vec3							pos;
	t_vec3							dir;
	float							speed;
}									t_actor;

typedef struct s_player_input
{
	int								move_forward;
	int								move_backward;
	int								strafe_left;
	int								strafe_right;
	int								rotate_left;
	int								rotate_right;
	int								pitch_up;
	int								pitch_down;
	int								interact;
	int								shoot;
	int								reload;
	int								sprint;
	int								crouch;
	int								jump;
	int								switch_weapon;
}									t_player_input;

typedef struct s_mouse
{
	int								lmb_pressed;
	int								rmb_pressed;
	int								prev_x;
	int								prev_y;
	int								captured;
}									t_mouse;

typedef struct s_player_controller
{
	struct s_player					*player;
	t_player_input					input;
	t_mouse							mouse;
}									t_player_controller;

/* ── Weapon types ──────────────────────────────────────────────────────── */

typedef enum e_weapon_type
{
	WEAPON_NONE = -1,
	WEAPON_PISTOL = 0,
	WEAPON_MELEE = 1,
	WEAPON_PROJECTILE = 2,
}									t_weapon_type;

typedef struct s_weapon_state
{
	int								type;
	int								has_weapon;
	int								ammo[WEAPON_COUNT];
	int								cooldown;
}									t_weapon_state;

/* ── Debug shapes ──────────────────────────────────────────────────────── */

typedef enum e_debug_type
{
	DEBUG_SPHERE,
	DEBUG_BOX,
	DEBUG_ARROW
}									t_debug_type;

typedef struct s_debug_shape
{
	t_debug_type					type;
	t_vec3							p1;
	t_vec3							p2;
	float							radius;
	t_vec3							color;
	int								lifetime_us;
	bool							active;
}									t_debug_shape;

typedef struct s_dbg_style
{
	t_vec3							color;
	int								lifetime_ms;
}									t_dbg_style;

# define MAX_DEBUG_SHAPES 64

/* ── Game entities ─────────────────────────────────────────────────────── */

typedef struct s_player
{
	t_actor							actor;
	float							pitch_offset;
	t_vec3							render_pos;
	t_vec3							render_dir;
	float							render_pitch_offset;
	float							pos_z;
	float							vel_z;
	float							render_pos_z;
	float							fov;
	int								health;
	int								armor;
	t_weapon_state					weapon_state;
	t_player_controller				controller;
}									t_player;

typedef enum e_door_anim_type
{
	DOOR_ANIM_OPENING,
	DOOR_ANIM_CLOSING
}									t_door_anim_type;

typedef struct s_door_anim_instance
{
	t_vec2s							pos;
	t_anim_state					state;
	t_door_anim_type				type;
	bool							active;
	float							open_amount;
}									t_door_anim_instance;

# define MAX_ACTIVE_DOORS 16
# define MAX_PUSH_WALLS 16
# define PUSH_WALL_SPEED 1.0f

typedef struct s_push_wall
{
	t_vec2s							s;
	t_vec2i							d;
	float							offset;
	bool							active;
}									t_push_wall;

typedef enum e_entity_type
{
	ENTITY_NONE = 0,
	ENTITY_ENEMY_GUARD,
	ENTITY_ITEM_MEDKIT,
	ENTITY_ITEM_AMMO,
	ENTITY_ITEM_SHIELD,
	ENTITY_PROJECTILE,
}									t_entity_type;

typedef enum e_entity_state
{
	ENTITY_STATE_IDLE,
	ENTITY_STATE_WALK,
	ENTITY_STATE_SPRINT,
	ENTITY_STATE_ATTACK,
	ENTITY_STATE_DIE
}									t_entity_state;

typedef struct s_entity
{
	t_vec2							pos;
	t_vec2							target_pos;
	t_vec2							vel;
	t_entity_type					type;
	t_entity_state					state;
	int								health;
	int								armor;
	t_anim_state					anim;
	t_anim_clip						*clip;
	float							shoot_cooldown;
	float							idle_timer;
	float							aggro_timer;
	t_vec2							last_seen_pos;
	float							anim_speed_scale;
	float							current_speed;
	int								lifetime_us;
	bool							active;
}									t_entity;

# define MAX_ENTITIES 256

typedef struct s_world
{
	t_map							*map;
	t_player						player;
	t_anim							weapon_anim;
	t_texture						crosshair;
	t_debug_shape					debug_shapes[MAX_DEBUG_SHAPES];
	uint64_t						last_frame_time_us;
	float							fps;
	float							frame_time_ms;
	t_anim_clip						*door_open_clip;
	t_anim_clip						*door_close_clip;
	t_door_anim_instance			active_doors[MAX_ACTIVE_DOORS];
	t_push_wall						push_walls[MAX_PUSH_WALLS];
	int								*push_grid;
	t_anim_mgr						anim_mgr;
	t_tex_cache						tex_cache;
	int								*door_grid;
	t_entity						entities[MAX_ENTITIES];
	size_t							entity_count;
	t_anim_clip						*enemy_guard_clip;
	t_anim_clip						*medkit_clip;
	t_anim_clip						*ammo_clip;
	t_anim_clip						*shield_clip;
	t_anim_clip						*monster_idle;
	t_anim_clip						*monster_walk;
	t_anim_clip						*monster_sprint;
	t_anim_clip						*monster_attack;
	t_anim_clip						*monster_die;
}									t_world;

typedef struct s_input
{
	t_window						*window;
	t_world							*world;
}									t_input;

typedef struct s_app
{
	t_window						*window;
	t_world							*world;
}									t_app;

void								init_gameplay_maps(t_world *world,
										t_map *tmp_map);
void								init_player(t_player *player);
t_keymap_entry						*get_keyboard_keymap(void);
void								handle_key_press(int keycode,
										t_player_controller *controller);
void								handle_key_release(int keycode,
										t_player_controller *controller);
void								init_keyboard_input(t_window *window,
										t_world *world);
void								fire_weapon(t_world *world);
void								update_gameplay(t_world *world,
										int elapsed_us);
void								render_gameplay(t_window *window,
										t_world *world);

void								init_gameplay(t_world *world,
										t_window *window, char *map_file,
										t_app *app);
int									load_map_textures(t_map *map,
										t_world *world, t_app *app);
void								setup_gameplay_hooks(t_app *app);
int									on_key_press(int keycode, void *param);
int									on_key_release(int keycode, void *param);
int									on_destroy(void *param);
int									on_loop(void *param);

void								init_player_from_map(t_player *player,
										t_map *map);

void								init_pistol(t_anim *wa, t_window *win,
										t_world *world);

void								rotate_player(t_actor *actor, float angle);
void								apply_movement(t_world *world,
										t_vec2 delta);

void								try_interact_door(t_world *world);

int									get_weapon_max_ammo(int type);
int									get_weapon_fire_cooldown(int type);
void								set_reload_ammo(t_weapon_state *state);

void								init_app(t_app *app, t_window *window,
										t_world *world, char *map_file);
void								init_mouse_hook(t_window *window,
										t_player_controller *controller);

void								render_crosshair(t_window *win,
										t_world *world);

void								add_debug_sphere(t_world *world, t_vec3 pos,
										float radius, t_dbg_style style);
void								add_debug_box(t_world *world, t_vec3 min,
										t_vec3 max, t_dbg_style style);
void								add_debug_arrow(t_world *world,
										t_vec3 start, t_vec3 end,
										t_dbg_style style);
void								update_debug_shapes(t_world *world,
										int elapsed_us);
void								render_debug_shapes(t_window *win,
										t_world *world);
void								render_fps_counter(t_window *win,
										t_world *world);
void								render_hud(t_window *win, t_world *world);
void								update_door_animations(t_world *world,
										int elapsed_us);

/* ── update.c ─────────────────────────────────────────────────────────── */

void								handle_movement_input(t_world *world,
										t_player_input *input, float speed,
										float dt);
void								apply_action_flags(t_world *world,
										int elapsed_us);

/* ── update_utils.c ───────────────────────────────────────────────────── */

bool								handle_shooting(t_world *world, bool fired);
void								update_fps(t_world *world, int elapsed_us);
void								tick_anim(t_world *world, bool shot,
										bool reload, int el);
void								tick_entities(t_world *world,
										int elapsed_us);
void								handle_weapon_update(t_world *world,
										bool *shot, bool *reload);

/* ── door animations ─────────────────────────────────────────────────── */

void								tick_door(t_world *world, int i,
										int elapsed_us);
void								finish_door(t_world *world, int i);

/* ── mouse hooks ─────────────────────────────────────────────────────── */

int									handle_mouse_press(int button, int x, int y,
										void *param);
int									handle_mouse_release(int button, int x,
										int y, void *param);
int									handle_mouse_motion(int x, int y,
										void *param);
void								update_mouse_look(t_window *win,
										t_player_controller *ctrl);

/* ── weapon fire ─────────────────────────────────────────────────────── */

bool								is_active_door_passable(t_world *world,
										t_dda *d, t_vec2 ray);
void								calculate_impact(t_world *world, t_vec2 ray,
										float dist, t_vec3 *impact);
void								handle_enemy_hit(t_world *world,
										t_entity *ent);
void								check_entity_damage(t_world *world,
										t_vec2 ray, float dist);

/* ── entities ─────────────────────────────────────────────────────────── */

void								spawn_entity(t_world *world,
										t_entity_type type, t_vec2 pos);
void								spawn_projectile(t_world *world, t_vec2 pos,
										t_vec2 dir);
void								tick_projectile(t_world *world,
										t_entity *ent, float dt);
void								tick_monster(t_world *world, t_entity *ent,
										float dt);
void								tick_item(t_world *world, t_entity *ent);
bool								check_los(t_world *world, t_vec2 a,
										t_vec2 b);
void								update_aggro(t_world *world, t_entity *ent,
										t_vec2 p_pos, float dt);
void								handle_attack(t_world *world,
										t_entity *ent);
void								handle_chase(t_world *world, t_entity *ent,
										t_vec2 *t, float *s);
void								handle_patrol(t_world *world, t_entity *ent,
										float dt);
void								init_entities(t_world *world);
void								apply_move(t_world *world, t_entity *ent,
										t_vec2 t, float s);
void								set_state(t_entity *ent,
										t_entity_state new_state,
										t_anim_clip *clip);
void								tick_anim_ent(t_world *world, t_entity *ent,
										int elapsed_us);

void								damage_player(t_world *world, int amount);

/* ── push walls ───────────────────────────────────────────────────────── */

bool								try_interact_push(t_world *world);
void								tick_push_walls(t_world *world, float dt);
void								sync_push_grid(t_world *world);
void								drop_loot(t_world *world, t_vec2 pos);

void								init_gameplay_assets(t_world *world,
										t_window *window, t_app *app);

bool								pf_closed_is_player_walkable(char c);
bool								pf_closed_check_tile(t_map *map, size_t x,
										size_t y);
bool								pf_closed_check_sprite_cells(t_map *map);
bool								pf_closed_check_hborders(t_map *map);

#endif
