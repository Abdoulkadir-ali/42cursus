/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_internal.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 19:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 17:49:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROPS_INTERNAL_H
# define PROPS_INTERNAL_H

# include "parsing.h"

int	last_targets(t_scene *s, t_object **arr_out);
int	prop_mat(char **t, int n, t_scene *s);
int	prop_float(char **t, int n, t_scene *s, int field);
int	prop_emit_color(char **t, int n, t_scene *s);
int	prop_name(char **t, int n, t_scene *s);
int	dispatch_one_prop(char **t, int n, t_scene *s);

#endif
