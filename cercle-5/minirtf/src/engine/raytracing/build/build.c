/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 00:56:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/28 01:20:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

static bool	alloc_arrays(t_bd *bd)
{
	bd->boxes = malloc(sizeof(t_aabb) * bd->n);
	bd->centers = malloc(sizeof(t_vec3) * bd->n);
	bd->stack = malloc(sizeof(t_task) * (bd->n * 2 + 64));
	return (bd->boxes && bd->centers && bd->stack);
}

static void	init_arrays(t_bvh *bvh, t_object *objs, t_bd *bd)
{
	size_t	i;

	i = 0;
	while (i < bd->n)
	{
		bd->boxes[i] = obj_box(&objs[i]);
		bd->centers[i] = obj_center(&objs[i]);
		bvh->indices[i] = i;
		i++;
	}
}

static void	cleanup(t_bd *bd)
{
	if (!bd)
		return ;
	free(bd->boxes);
	free(bd->centers);
	free(bd->stack);
}

static int	subdivide_and_push(t_bvh *bvh, t_bd *bd)
{
	int		res;
	t_sah	s;

	s.boxes = bd->boxes;
	s.centers = bd->centers;
	res = subdivide(bvh, bd->stack[--bd->sp], &s, bd->out);
	if (res == 1)
	{
		make_leaf(bvh, bd->out[0], bd->boxes, bvh->indices);
		make_leaf(bvh, bd->out[1], bd->boxes, bvh->indices);
		bd->stack[bd->sp++] = bd->out[0];
		bd->stack[bd->sp++] = bd->out[1];
	}
	return (1);
}

int	bvh_build(t_bvh *bvh, t_object *objs, int n_in)
{
	t_bd	bd;
	size_t	root;

	memset(bvh, 0, sizeof(*bvh));
	if (n_in <= 0)
		return (0);
	bd.n = (size_t)n_in;
	bvh->indices = malloc(sizeof(size_t) * bd.n);
	if (!bvh->indices || !alloc_arrays(&bd))
		return (cleanup(&bd), bvh_free(bvh), -1);
	bvh->n_indices = bd.n;
	init_arrays(bvh, objs, &bd);
	root = push_node(bvh);
	if (root == (size_t)-1)
		return (cleanup(&bd), bvh_free(bvh), -1);
	make_leaf(bvh, (t_task){root, 0, bd.n}, bd.boxes, bvh->indices);
	bd.stack[0] = (t_task){root, 0, bd.n};
	bd.sp = 1;
	while (bd.sp > 0)
		subdivide_and_push(bvh, &bd);
	return (cleanup(&bd), 0);
}
