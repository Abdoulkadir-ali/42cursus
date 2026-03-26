/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 09:41:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

# /* External dependencies */
# include "defines.h"
# include "gui.h"
# include "scene.h"

/* 3. FUNCTION PROTOTYPES */
int		run_app(const char *path);
t_gui	*init_app(const char *path, t_scene **scene, void *mlx);
int		start_app(t_gui *gui, t_scene *scene, void *mlx);
void	core_cleanup(t_scene *scene, t_gui *gui);

#endif