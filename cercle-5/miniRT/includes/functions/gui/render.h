#ifndef GUI_RENDER_PROTOTYPES_H
# define GUI_RENDER_PROTOTYPES_H

# include "types/types.h"
# include <sys/time.h>

# define TILE_SIZE 32

t_gui *gui_init(t_scene *scene, void *mlx);
void gui_destroy(t_gui *gui);
bool init_window(t_gui *gui);
void init_camera(t_gui *gui);
void gui_init_physics(t_gui *gui);
void gui_init_render(t_gui *gui);
void gui_render(t_gui *gui);
unsigned int color_blend(unsigned int dst, int src, float alpha);
void render_tiles(t_render *render);
void gui_update_hover(t_gui *gui);
void process_pixel(t_render *render, t_vec2i pos, char *pixel_addr);
void upscale_image(t_gui *gui);
void fullres_toggle(t_gui *gui);
void poll_map_job(t_gui *gui);
void clear_selection(t_gui *gui);
double update_delta(t_gui *gui);
void update_animations(t_gui *gui, double dt);
void update_physics_step(t_gui *gui, double dt);
void update_autorefresh(t_gui *gui);
void update_ambient(t_gui *gui);
const char *mesh_name(t_mesh *mesh);
void draw_char(t_gui *gui, unsigned char c, t_vec2i pos, unsigned int color);
int panel_color(t_panel panel, t_vec2i pos);

#endif
