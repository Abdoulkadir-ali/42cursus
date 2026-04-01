/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_map.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 20:02:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/01 13:39:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_MAP_H
# define GUI_MAP_H

# include "t_physics.h"

typedef struct s_map				t_map;

typedef struct s_map_entry
{
	char				*path;
	t_scene				*scene;
	t_scene_snap		snap;
	struct s_map_entry	*next;
}	t_map_entry;

struct s_map
{
	t_map_entry	*head;
	t_map_entry	*current;
	int			count;
};

typedef struct s_map_job
{
	pthread_t	tid;
	t_map_entry	*entry;
	bool		done;
	bool		active;
}	t_map_job;

#endif
