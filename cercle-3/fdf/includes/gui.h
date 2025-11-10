#ifndef GUI_H
# define GUI_H

// Forward declaration
typedef struct s_data	t_data;

/* ========== GUI CONSTANTS ========== */
# define GUI_PANEL_WIDTH 280
# define GUI_PADDING 15
# define GUI_LINE_HEIGHT 18
# define GUI_TITLE_HEIGHT 25

// Colors
# define GUI_BG_COLOR 0x1A1A1A
# define GUI_BORDER_COLOR 0x404040
# define GUI_TEXT_COLOR 0xE0E0E0
# define GUI_TITLE_COLOR 0x00D4FF
# define GUI_VALUE_COLOR 0x00FF88
# define GUI_KEY_COLOR 0xFFAA00

/* ========== GUI FUNCTIONS ========== */
// Initialize GUI image buffer
void	init_gui(t_data *data);

// Render the GUI control panel
void	render_gui(t_data *data);

// Draw text helpers
void	draw_text(t_data *data, int x, int y, char *text, int color);
void	draw_panel_background(t_data *data);
void	draw_controls_guide(t_data *data);
void	draw_speed_display(t_data *data);

#endif
