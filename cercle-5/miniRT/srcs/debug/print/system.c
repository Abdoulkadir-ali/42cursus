/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   system.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 20:30:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/09 20:30:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_scene(t_scene s)
{
	printf("scene(\n  name: %s\n", s.name ? s.name : "NULL");
	printf("  counts: spheres: %d, planes: %d, cylinders: %d, cones: %d, meshes: %d, animated: %d, lights: %d, materials: %d\n", \
		s.sphere_count, s.plane_count, s.cylinder_count, s.cone_count, s.mesh_count, s.anim_count, s.light_count, s.mat_count);
	printf("  ambient: ");
	print_ambient(s.ambient);
	printf("\n  camera: ");
	print_camera(s.camera);
	printf("\n)");
}

void	print_ray(t_ray r)
{
	printf("ray(\n  origin: ");
	print_vec3(r.origin);
	printf("\n  direction: ");
	print_vec3(r.direction);
	printf("\n  inv_dir: ");
	print_vec3(r.inv_dir);
	printf("\n  sign: [%d, %d, %d]\n)", r.sign[0], r.sign[1], r.sign[2]);
}

void	print_hit(t_hit h)
{
	printf("hit(\n  t: %.4f\n  point: ", h.t);
	print_vec3(h.point);
	printf("\n  normal: ");
	print_vec3(h.normal);
	printf("\n  uv: (%.4f, %.4f)\n  ref: type: %d, index: %d\n)", \
		h.u, h.v, h.ref.type, h.ref.index);
}

void	print_parser(t_parser p)
{
	printf("parser(\n  fd: %d\n  cursor: %zu\n  bytes_read: %zu\n  eof: %s\n)", \
		p.fd, p.cursor, p.bytes_read, p.eof ? "true" : "false");
}

void	print_gui(t_gui *g)
{
	printf("gui(\n  win: %dx%d\n  render: scale: %d, dirty: %s, fps: %.2f\n  map: %d maps, current: %d\n)", \
		g->win.width, g->win.height, g->render.scale, g->render.dirty ? "true" : "false", \
		g->render.fps, g->map_info.count, g->map_info.current_idx);
}

void	print_bvh_node(t_bvh_node *n, int depth)
{
	int	i;

	if (!n) return ;
	for (i = 0; i < depth; i++) printf("  ");
	printf("node(refs: %zu, leaf: %s, bbox: ", n->num_refs, (n->left || n->right) ? "no" : "yes");
	print_vec3(n->bbox.min);
	printf(" to ");
	print_vec3(n->bbox.max);
	printf(")\n");
	if (n->left) print_bvh_node(n->left, depth + 1);
	if (n->right) print_bvh_node(n->right, depth + 1);
}

void	print_bvh(t_bvh b)
{
	printf("bvh(root:\n");
	if (b.root) print_bvh_node(b.root, 1);
	else printf("  NULL\n");
	printf(")\n");
}
