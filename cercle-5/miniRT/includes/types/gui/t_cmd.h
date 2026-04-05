/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cmd.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:06:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_CMD_H
# define TYPES_CMD_H

# include <stdatomic.h>
# include "t_maths.h"
# include "t_scene.h"

# define CMD_QUEUE_SIZE 256

/*
** All mutation operations the editor can request.
** CMD_REBUILD_BVH is a catch-all for operations that the editor performs
** entirely on its own data (e.g. material edits through pointer) and just
** need the scene BVH to be rebuilt afterwards.
*/
typedef enum e_cmd_type
{
	CMD_NOP,
	CMD_SET_POS,
	CMD_SET_ROT,
	CMD_SET_SCALE,
	CMD_SET_MATERIAL,
	CMD_REBUILD_BVH,
}	t_cmd_type;

typedef struct s_cmd_set_transform
{
	t_type	obj_type;
	size_t	index;
	t_vec3		pos;
	t_vec3		scale;
	t_rotator	rot;
}	t_cmd_set_transform;

typedef struct s_cmd_set_material
{
	size_t	mat_id;
	t_material	material;
}	t_cmd_set_material;

/*
** A single editor command.  The union holds the payload for each type.
** Keep this struct small — it lives in a statically allocated ring buffer.
*/
typedef struct s_cmd
{
	t_cmd_type	type;
	union
	{
		t_cmd_set_transform		transform;
		t_cmd_set_material		material;
	}			data;
}	t_cmd;

/*
** Lock-free SPSC ring buffer.
** tail is written only by the MLX/editor thread (producer).
** head is written only by the render thread (consumer).
** No mutex needed — we just need acquire/release atomics.
*/
typedef struct s_cmd_queue
{
	t_cmd		slots[CMD_QUEUE_SIZE];
	_Atomic int	head;
	_Atomic int	tail;
}	t_cmd_queue;

#endif
