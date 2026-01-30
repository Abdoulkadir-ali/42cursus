/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot <copilot@local>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 19:10:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:10:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "libft.h"
# include "objects.h"
//CUSTOM
# include <fcntl.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCENES_INIT_CAP 2
# define SCENE_INIT_CAP 4

typedef struct s_scene
{
	char		*name;
	t_object	**objects;
	size_t		count;
	size_t		capacity;
}				t_scene;

typedef struct s_scenes
{
	t_scene		*scenes;
	size_t		count;
	size_t		capacity;
}				t_scenes;

/* Scene lifecycle */
t_scene			*create_scene(const char *name);
bool			scene_add_object(t_scene *scene, t_object *obj);
void			destroy_scene(t_scene *scene);
void			print_scene(t_scene *scene);

/* Scenes container lifecycle */
t_scenes		*create_scenes(void);
bool			scenes_add(t_scenes *scenes, t_scene *scene);
void			destroy_scenes(t_scenes *scenes);

/* I/O */
t_scene			*scene_load_from_file(const char *path);

#endif
