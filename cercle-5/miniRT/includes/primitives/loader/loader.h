/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:11:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:15:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOADER_H
# define LOADER_H

/* Loader Buffer Sizes */
/* PARSER_BUF_SIZE is defined in parser.h */

/* Core Dependencies */
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <unistd.h>
# include "utils.h"

/* Modular Loader Headers (Split) */
# include "fbx.h"
# include "fdf.h"
# include "glb.h"
# include "material.h"
# include "mesh.h"
# include "obj.h"
# include "rt.h"


#endif
