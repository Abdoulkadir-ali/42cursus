/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_style.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:14:21 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/10 16:37:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_STYLE_H
# define GUI_STYLE_H

typedef enum e_gui_style
{
	GUI_STYLE_TRON_BLUE,
	GUI_STYLE_TRON_ORANGE,
	GUI_STYLE_MATRIX,
	GUI_STYLE_CYBERPUNK,
	GUI_STYLE_NEON_GRID,
	GUI_STYLE_COUNT
}	t_gui_style;

typedef struct s_gui_theme
{
	int		background;
	int		border;
	int		text_primary;
	int		text_secondary;
	int		accent;
	int		highlight;
}	t_gui_theme;

/* GUI styling functions */
void		cycle_gui_style(struct s_data *data);
t_gui_theme	get_gui_theme(t_gui_style style);
int			get_gui_background_color(t_gui_style style);
int			get_gui_accent_color(t_gui_style style);
int			get_gui_border_color(t_gui_style style);
int			get_gui_text_color(t_gui_style style);

extern const char	*g_gui_style_names[GUI_STYLE_COUNT];

#endif
