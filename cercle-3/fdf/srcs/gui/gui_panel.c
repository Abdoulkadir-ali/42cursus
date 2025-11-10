#include "fdf.h"
#include "gui.h"
#include "projection.h"

// Get accent color based on current GUI style
static int	get_accent_color(t_data *data)
{
	return (get_gui_accent_color(data->camera.gui_style));
}

// Initialize GUI image buffer
void	init_gui(t_data *data)
{
	data->gui_img = mlx_new_image(data->mlx_ptr, GUI_PANEL_WIDTH,
			data->win_height);
	data->gui_addr = mlx_get_data_addr(data->gui_img, &data->gui_bpp,
			&data->gui_line_len, &data->gui_endian);
}

// Put pixel in GUI image
static void	gui_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= GUI_PANEL_WIDTH || y < 0 || y >= data->win_height)
		return ;
	dst = data->gui_addr + (y * data->gui_line_len + x * (data->gui_bpp / 8));
	*(unsigned int *)dst = color;
}

// Draw a filled rectangle in GUI image
static void	draw_rect(t_data *data, t_vec2 pos, t_vec2 size, int color)
{
	int	x;
	int	y;

	y = pos.y;
	while (y < pos.y + size.y && y < data->win_height)
	{
		x = pos.x;
		while (x < pos.x + size.x && x < GUI_PANEL_WIDTH)
		{
			gui_pixel_put(data, x, y, color);
			x++;
		}
		y++;
	}
}

// Draw the panel background with style-aware neon borders
void	draw_panel_background(t_data *data)
{
	t_vec2	pos;
	t_vec2	size;
	int		bg_color;
	int		accent;
	int		i;

	bg_color = get_gui_background_color(data->camera.gui_style);
	accent = get_accent_color(data);
	pos.x = 0;
	pos.y = 0;
	size.x = GUI_PANEL_WIDTH;
	size.y = data->win_height;
	draw_rect(data, pos, size, bg_color);
	i = 0;
	while (i < 3)
	{
		pos.x = GUI_PANEL_WIDTH - 3 + i;
		size.x = 1;
		size.y = data->win_height;
		draw_rect(data, pos, size, accent);
		i++;
	}
}

// Draw text at position
void	draw_text(t_data *data, int x, int y, char *text, int color)
{
	mlx_string_put(data->mlx_ptr, data->win_ptr, x, y, color, text);
}

// Draw the controls guide
void	draw_controls_guide(t_data *data)
{
	int	y;

	y = GUI_PADDING;
	
	// Title
	draw_text(data, GUI_PADDING, y, "CONTROLS GUIDE", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	
	// Mouse controls
	draw_text(data, GUI_PADDING, y, "Mouse:", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "LMB + Drag", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Rotate", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "RMB + Drag", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Color Shift", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "MMB + Drag", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Depth Cut", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "Scroll", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Zoom", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "Ctrl + Scroll", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Zoom Speed", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT + 5;
	
	// Keyboard controls
	draw_text(data, GUI_PADDING, y, "Keyboard:", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "Arrow Keys", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Move", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "Ctrl + Up", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Speed ++", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "Ctrl + Down", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Speed --", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "P", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Projection", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "N", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Next Map", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "S", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Style", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "R", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Reset View", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y, "ESC", GUI_KEY_COLOR);
	draw_text(data, GUI_PADDING + 120, y, "Exit", GUI_TEXT_COLOR);
}

// Helper to convert double to string with 2 decimals
static void	format_speed(double speed, char *buffer)
{
	int	whole;
	int	decimal;

	whole = (int)speed;
	decimal = (int)((speed - whole) * 100);
	buffer[0] = '0' + (whole / 10);
	buffer[1] = '0' + (whole % 10);
	buffer[2] = '.';
	buffer[3] = '0' + (decimal / 10);
	buffer[4] = '0' + (decimal % 10);
	buffer[5] = 'x';
	buffer[6] = '\0';
}

// Draw dampening display
static void	draw_dampening_display(t_data *data)
{
	int		y;
	char	depth_str[20];
	int		visible_percent;

	y = data->win_height - 240;
	draw_text(data, GUI_PADDING, y, "DEPTH DAMPENING", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	if (data->camera.dampening_threshold <= data->map->min_z)
	{
		draw_text(data, GUI_PADDING + 10, y, "OFF", GUI_VALUE_COLOR);
	}
	else
	{
		visible_percent = (int)(100.0 * (data->map->max_z
					- data->camera.dampening_threshold)
				/ (data->map->max_z - data->map->min_z));
		depth_str[0] = '0' + (visible_percent / 10);
		depth_str[1] = '0' + (visible_percent % 10);
		depth_str[2] = '%';
		depth_str[3] = ' ';
		depth_str[4] = 'v';
		depth_str[5] = 'i';
		depth_str[6] = 's';
		depth_str[7] = 'i';
		depth_str[8] = 'b';
		depth_str[9] = 'l';
		depth_str[10] = 'e';
		depth_str[11] = '\0';
		draw_text(data, GUI_PADDING + 10, y, depth_str, GUI_VALUE_COLOR);
	}
}

// Draw visual style display
static void	draw_style_display(t_data *data)
{
	int		y;
	int		accent;

	y = data->win_height - 240;
	accent = get_accent_color(data);
	draw_text(data, GUI_PADDING, y, "GUI STYLE", accent);
	y += GUI_TITLE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y,
		(char *)g_gui_style_names[data->camera.gui_style], accent);
}

// Draw projection display
static void	draw_projection_display(t_data *data)
{
	int	y;

	y = data->win_height - 180;
	draw_text(data, GUI_PADDING, y, "PROJECTION", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	draw_text(data, GUI_PADDING + 10, y,
		(char *)g_projection_names[data->camera.projection], GUI_VALUE_COLOR);
}

// Draw speed display
void	draw_speed_display(t_data *data)
{
	int		y;
	char	move_str[10];
	char	zoom_str[10];

	y = data->win_height - 120;
	draw_text(data, GUI_PADDING, y, "SPEED SETTINGS", GUI_TITLE_COLOR);
	y += GUI_TITLE_HEIGHT;
	draw_text(data, GUI_PADDING, y, "Move Speed:", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	format_speed(data->camera.move_speed, move_str);
	draw_text(data, GUI_PADDING + 20, y, move_str, GUI_VALUE_COLOR);
	y += GUI_LINE_HEIGHT + 5;
	draw_text(data, GUI_PADDING, y, "Zoom Speed:", GUI_TEXT_COLOR);
	y += GUI_LINE_HEIGHT;
	format_speed(data->camera.zoom_speed, zoom_str);
	draw_text(data, GUI_PADDING + 20, y, zoom_str, GUI_VALUE_COLOR);
}

// Main GUI rendering function
void	render_gui(t_data *data)
{
	draw_controls_guide(data);
	draw_style_display(data);
	draw_dampening_display(data);
	draw_projection_display(data);
	draw_speed_display(data);
}
