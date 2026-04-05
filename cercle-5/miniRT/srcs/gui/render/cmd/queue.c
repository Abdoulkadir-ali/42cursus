/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/05 15:08:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	cmd_queue_init(t_cmd_queue *q)
{
	atomic_init(&q->head, 0);
	atomic_init(&q->tail, 0);
}

void	cmd_queue_destroy(t_cmd_queue *q)
{
	(void)q;
}

/*
** Enqueue a command from the MLX/editor thread.
** Silently drops commands when the queue is full to avoid blocking the GUI.
** 256 slots is far more than one frame of editor interaction can produce.
*/
/*
** Producer side (MLX thread).  Only writes tail.
** Loads head with acquire to check fullness — no mutex needed.
*/
void	cmd_enqueue(t_gui *gui, t_cmd cmd)
{
	t_cmd_queue	*q;
	int			tail;
	int			next;

	q = &gui->cmd_queue;
	tail = atomic_load_explicit(&q->tail, memory_order_relaxed);
	next = (tail + 1) % CMD_QUEUE_SIZE;
	if (next == atomic_load_explicit(&q->head, memory_order_acquire))
	{
		ft_print_debug("[CMD] queue full — command dropped (type=%d)\n", cmd.type);
		return ;
	}
	q->slots[tail] = cmd;
	atomic_store_explicit(&q->tail, next, memory_order_release);
}

/*
** Drain all pending commands and apply them to the scene.
** Called exclusively from the render thread at the top of render_frame —
** the render thread is the only writer of scene state.
*/
static void	apply_cmd(t_gui *gui, t_cmd *cmd)
{
	t_cmd_set_transform	*tr;
	t_scene				*sc;

	sc = gui->scene;
	if (!sc)
		return ;
	if (cmd->type == CMD_SET_POS)
	{
		tr = &cmd->data.transform;
		if (tr->obj_type == TYPE_SPHERE && tr->index < sc->sphere_count)
		{
			sc->spheres[tr->index].transform.pos = tr->pos;
			sc->spheres[tr->index].phys.pos = tr->pos;
		}
		else if (tr->obj_type == TYPE_PLANE && tr->index < sc->plane_count)
			sc->planes[tr->index].transform.pos = tr->pos;
		else if (tr->obj_type == TYPE_LIGHT && tr->index < sc->light_count)
			sc->lights[tr->index].transform.pos = tr->pos;
		gui->render.bvh_needs_rebuild = 1;
	}
	else if (cmd->type == CMD_SET_ROT)
	{
		tr = &cmd->data.transform;
		if (tr->obj_type == TYPE_PLANE && tr->index < sc->plane_count)
		{
			sc->planes[tr->index].transform.rotation = tr->rot;
			sc->planes[tr->index].transform.forward = vec3_norm(
					mat4_mul_vec3(mat4_rotation(tr->rot), vec3(0, 0, -1)));
		}
		gui->render.bvh_needs_rebuild = 1;
	}
	else if (cmd->type == CMD_SET_SCALE)
	{
		tr = &cmd->data.transform;
		if (tr->obj_type == TYPE_SPHERE && tr->index < sc->sphere_count)
			sc->spheres[tr->index].transform.scale = tr->scale;
		gui->render.bvh_needs_rebuild = 1;
	}
	else if (cmd->type == CMD_SET_MATERIAL)
	{
		if (cmd->data.material.mat_id < sc->mat_count)
			sc->materials[cmd->data.material.mat_id] = cmd->data.material.material;
	}
	else if (cmd->type == CMD_REBUILD_BVH)
		gui->render.bvh_needs_rebuild = 1;
}

/*
** Consumer side (render thread).  Only writes head.
** Loads tail with acquire — no mutex needed.
** Empty check: two atomic loads, zero syscalls.
*/
void	cmd_drain(t_gui *gui)
{
	t_cmd_queue	*q;
	int			head;
	int			tail;

	q = &gui->cmd_queue;
	head = atomic_load_explicit(&q->head, memory_order_relaxed);
	tail = atomic_load_explicit(&q->tail, memory_order_acquire);
	while (head != tail)
	{
		apply_cmd(gui, &q->slots[head]);
		head = (head + 1) % CMD_QUEUE_SIZE;
		tail = atomic_load_explicit(&q->tail, memory_order_acquire);
	}
	atomic_store_explicit(&q->head, head, memory_order_release);
}
