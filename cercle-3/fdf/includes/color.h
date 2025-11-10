#ifndef COLOR_H
# define COLOR_H

// RGB structure
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Color gradient presets
typedef struct s_gradient
{
	int	color_low;
	int	color_mid;
	int	color_high;
}	t_gradient;

// RGB extraction functions
int		get_red(int color);
int		get_green(int color);
int		get_blue(int color);
t_rgb	get_rgb(int color);

// Color creation and manipulation
int		create_color(int r, int g, int b);
int		create_color_rgb(t_rgb rgb);
int		shift_color(int color, int red_shift, int blue_shift, int green_shift);

// Color interpolation and gradient
int		interpolate_color(int color1, int color2, double ratio);
int		get_height_color(int z, int min_z, int max_z);

#endif
