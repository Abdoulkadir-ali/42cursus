/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 12:49:24 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 12:49:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CORE_H
# define CORE_H

# include "main.h"
# include <stdbool.h>
# include <locale.h>
# include "helpers.h"
# include "primitives.h"
# include "engines.h"
# include "gui.h"

bool	is_rt_file(const char *name);
bool	is_directory(const char *path);
char	*first_rt_in_dir(const char *dir);

#endif