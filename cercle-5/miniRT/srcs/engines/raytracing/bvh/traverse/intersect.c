/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracing.h"

/**
 * @brief Handles second-tier BVH references dispatch mapping generic types to shapes.
 * 
 * Supports non-primitive elements including Box, Capsule, Static Mesh
 * geometry, and Animated Models. Validates the collision points using specific
 * ray-shape intersect tests.
 * 
 * @param r  The constant pointer pointing to the current rendering ray instance.
 * @param sc A mutable pointer referencing the full environment scene architecture.
 * @param rf BVH reference descriptor containing the specific type index identifiers.
 * @param h  Hit record tracker storing hit distance properties limits and characteristics.
 * 
 * @return `true` if a collision is found with `hit` matching correctly, `false` otherwise.
 */
static bool	dispatch_rest(const t_ray *r, t_scene *sc, t_bvh_ref rf, t_hit *h)
{
	if (rf.type == TYPE_BOX)
		return (intersect_box(r, &sc->boxes[rf.index], h));
	if (rf.type == TYPE_CAPSULE)
		return (intersect_capsule(r, &sc->capsules[rf.index], h));
	if (rf.type == TYPE_MESH)
		return (intersect_mesh(r, &sc->meshes[rf.index], h));
	if (rf.type == TYPE_ANIM)
		return (intersect_mesh(r, &sc->animated[rf.index].base, h));
	return (false);
}

/**
 * @brief Primary dispatch evaluating generic ray intersections against core shapes.
 * 
 * Routes incoming ray-collisions tests selectively across Sphere, Plane, Cylinder,
 * Cone, Triangles, Rectangles, and Primitive Pyramids. Cascades residual types 
 * onto the `dispatch_rest` subroutine to maintain compact and scalable code.
 * 
 * @param ray   The pointer to active rendering ray properties being currently tracked.
 * @param scene The entire configured virtual scene hosting primitive coordinates.
 * @param ref   A metadata referencing structure specifying target identification parameters.
 * @param hit   Output parameter configured and filled by bounding-level computations.
 * 
 * @return Value representing boolean collision existence. Returns hit truth values.
 */
static bool	dispatch_intersect(const t_ray *ray, t_scene *scene,
		t_bvh_ref ref, t_hit *hit)
{
	if (ref.type == TYPE_SPHERE)
		return (intersect_sphere(ray, &scene->spheres[ref.index], hit));
	if (ref.type == TYPE_PLANE)
		return (intersect_plane(ray, &scene->planes[ref.index], hit));
	if (ref.type == TYPE_CYLINDER)
		return (intersect_cylinder(ray, &scene->cylinders[ref.index], hit));
	if (ref.type == TYPE_CONE)
		return (intersect_cone(ray, &scene->cones[ref.index], hit));
	if (ref.type == TYPE_TRI)
		return (intersect_tri_shape(ray, &scene->tris[ref.index], hit));
	if (ref.type == TYPE_RECT)
		return (intersect_rect(ray, &scene->rects[ref.index], hit));
	if (ref.type == TYPE_PYRAMID)
		return (intersect_pyramid(ray, &scene->pyramids[ref.index], hit));
	return (dispatch_rest(ray, scene, ref, hit));
}

/**
 * @brief Public interface exposing generic object hit detections for external callers.
 * 
 * Invokes the type dispatching mechanics mapping a leaf reference metadata.
 * It directly encapsulates hit success registering reference indices, bridging
 * recursive or linear BVH leaf interactions with global scene geometries.
 * 
 * @param ray   Information struct for line segment ray testing containing origins.
 * @param scene Pointee to array buffers carrying instances representing environment assets.
 * @param ref   Context mapping identifying the node's primitive class category array index.
 * @param hit   Aggregator maintaining best hit-t and returning reference struct properties.
 * 
 * @return `true` indicating the `ray` perfectly intercepted a primitive shape. `false` on miss.
 */
bool	intersect_object(const t_ray *ray, t_scene *scene, t_bvh_ref ref,
		 t_hit *hit)
{
	bool	res;

	res = dispatch_intersect(ray, scene, ref, hit);
	if (res)
		hit->ref = ref;
	return (res);
}

/**
 * @brief Principal entry point for the bounding volume hierarchy (BVH) ray traversal loop.
 * 
 * Validates the inputs and initializes a clean traversal state for the hit registry.
 * Dispatches to `run_traverse_loop` to iteratively walk the BVH tree looking
 * for the closest valid shape intersection with the scene's objects.
 * 
 * @param bvh A constant pointer to the current hierarchy containing spatial nodes.
 * @param ray A constant pointer to the active rendering ray traversing space.
 * @param hit Pointer to the hit record struct receiving distance and nearest intersected object reference.
 * 
 * @return Returns `true` if a collision occurred configuring the `hit` wrapper. `false` if `hit` was unharmed.
 */
bool	bvh_intersect(const t_bvh *bvh, const t_ray *ray, t_hit *hit)
{
	if (!bvh || bvh->num_nodes == 0)
		return (false);
	hit->t = MAX_VALUE;
	hit->ref.type = TYPE_NONE;
	return (run_traverse_loop(bvh, ray, hit));
}