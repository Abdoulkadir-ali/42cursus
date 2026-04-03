/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:45:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:29:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "helpers.h"
# include "surface.h"
# include "types.h"

/* Resource Factory (srcs/objects/meshes/resource.c) */
bool					mesh_resource_add_mesh(t_mesh_resource *res,
							t_mesh mesh);
size_t					mesh_resource_add_material(t_mesh_resource *res,
							const char *name, bool *error);
void					mesh_resource_init(t_mesh_resource *res);
void					mesh_resource_free(t_mesh_resource *res);
void					mesh_build_bvh(t_mesh *mesh);
void					mesh_free(t_mesh *mesh);
void					mesh_apply_transform(t_mesh *mesh,
							t_transform transform);

/* BVH Build Internal (srcs/objects/mesh/bvh/) */
bool					bvh_prepare(t_mbvh *bvh, t_mesh *mesh);
size_t					build_mesh_recursive(t_mbvh *bvh, size_t first,
							size_t count);
void					bvh_copy_indices(t_mesh *mesh, t_mbvh *bvh);
void					mesh_build_tri_cache(t_mesh *mesh);
void					debug_print_bvh_build(size_t tri_count, size_t depth,
							bool start);
void					bvh_update_node_bounds(t_mbvh_node *node, t_mbvh *bvh,
							size_t first, size_t count);
void					bvh_get_triangle_info(t_mesh *mesh, size_t tri_idx,
							t_mesh_build_item *out);
void					bvh_axis_min_max(t_aabb *bounds, int axis,
							double *min, double *max);
void					bvh_bins_init(t_bin *bins);
void					bvh_fill_bins(t_bvh_bins *b);
void					bvh_sweep_left(t_bin *bins, double *left_area,
							size_t *left_counts);
void					bvh_sweep_right(t_bvh_split *s, int axis);
bool					bvh_find_split(t_bvh_find *f);
size_t					bvh_make_leaf(t_mbvh_node *node, size_t first,
							size_t count, t_index idx);
size_t					bvh_partition_items(t_mesh_build_item *items,
							size_t count, int axis, double split_val);
bool					bvh_try_split(t_bvh_try *bvh);
void					bvh_eval_axis(t_bvh_eval *e);
void					bvh_centroid_bounds(t_mbvh *bvh, int first, int count,
							t_aabb *out);

/* Tracing Internal */
bool					intersect_tri_precomp(const t_ray *ray,
							const t_tri_precomp *tc, double *t, t_vec2 *uv);
bool					intersect_triangle_fast(const t_ray *ray,
							t_vec3 v[3], double *t, t_vec2 *uv);
void					update_mesh_hit(t_mesh_hit *hit);
bool					traverse_occlude(t_mesh *mesh, const t_ray *ray,
							double dist);
size_t					pick_occ_children(t_mesh *mesh, t_index node_idx,
							const t_ray *ray, t_occ *occ);
bool					leaf_occluded(t_mesh *mesh, t_mbvh_node *node,
							const t_ray *ray, double dist);
void					process_mesh_leaf(t_mesh *mesh, t_mbvh_node *node,
							const t_ray *ray, t_trace *trace);
size_t					pick_children(t_mesh *mesh, t_index node_idx,
							const t_ray *ray, t_trace *trace);
void					test_children(t_mesh *mesh, t_index node_idx,
							const t_ray *ray, t_child *c);
size_t					select_child(t_child *c, t_trace *trace);
void					intersect_init(t_trace *trace, struct s_hit *hit);
void					intersect_traverse_mesh(t_mesh *mesh, const t_ray *ray,
							t_trace *trace);
bool					intersect_finish_hit(t_trace *trace, t_mesh *mesh,
							struct s_hit *hit, const t_ray *ray);

/* Mesh Scene Addition (srcs/primitives/scene/add/objects/) */
bool					scene_add_objects(t_scene *scene, const char *path);
bool					scene_add_mesh(t_scene *scene, t_mesh mesh);
bool					scene_add_mesh_file(t_scene *scene, const char *path);
bool					mesh_build_resource(const char *path,
							t_mesh_resource *res);
bool					scene_add_collection(t_scene *scene, t_parse_obj *item);
bool					scene_add_animated(t_scene *scene,
							t_skinned_mesh animated);
bool					scene_add_group(t_scene *scene, t_mesh_group g);
bool					scene_add_group_for_subs(t_scene *scene,
							const char *path, size_t start_mesh);

/* Cache (srcs/primitives/scene/add/objects/mesh/cache/) */
size_t					find_cache_idx(t_scene *scene, const char *path);
t_model_cache			*get_cache_entry(t_scene *scene, size_t idx);
bool					mesh_cache_has(t_scene *scene, const char *path);
bool					mesh_cache_save(t_scene *scene, const char *path,
							size_t start_mesh);
bool					mesh_cache_restore(t_scene *scene, const char *path);

# ifndef EPSILON
#  define EPSILON 1e-3
# endif

#endif