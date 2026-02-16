/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contacts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 18:00:00 by antigravity       #+#    #+#             */
/*   Updated: 2026/02/16 18:00:00 by antigravity      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics_internal.h"

/* 
 * Queries BVH for potential pairs and calls narrow-phase.
 * Fills the contacts array. Returns number of contacts.
 */
static int query_sphere(t_scene *s, int idx, t_contact *c, int count, int max)
{
    t_bvh_node  *stack[128];
    int         sp;
    t_sphere    *sphere;
    t_aabb      saabb;
    t_bvh_node  *node;

    sphere = &s->spheres[idx];
    if (sphere->phys.is_static) return (count);
    saabb = sphere_aabb(sphere);
    sp = 0;
    if (s->bvh && s->bvh->root)
        stack[sp++] = s->bvh->root;

    while (sp > 0 && count < max)
    {
        node = stack[--sp];
        if (!node) continue;
        // Optimization: check node bbox overlap
        if (node->bbox.max.x < saabb.min.x || node->bbox.min.x > saabb.max.x) continue;
        if (node->bbox.max.y < saabb.min.y || node->bbox.min.y > saabb.max.y) continue;
        if (node->bbox.max.z < saabb.min.z || node->bbox.min.z > saabb.max.z) continue;

        if (node->num_refs > 0)
        {
            for (size_t i = 0; i < node->num_refs && count < max; ++i)
            {
                t_bvh_ref ref = node->refs[i];
                if (ref.type == TYPE_SPHERE)
                {
                    if (ref.index <= idx) continue; /* Avoid duplicates */
                    if (collide_sphere_sphere(sphere, &s->spheres[ref.index], &c[count]))
                        count++;
                }
                else if (ref.type == TYPE_MESH)
                {
                    if (collide_sphere_mesh(sphere, &s->meshes[ref.index], &c[count]))
                        count++;
                }
            }
        }
        else
        {
            if (node->left) stack[sp++] = node->left;
            if (node->right) stack[sp++] = node->right;
        }
    }

    /* Check global planes */
    {
        int p = 0;
        while (p < s->plane_count && count < max)
        {
             if (collide_sphere_plane(sphere, &s->planes[p], &c[count]))
                 count++;
             p++;
        }
    }
    return (count);
}

int generate_contacts(t_scene *scene, t_contact *contacts, int max_c)
{
    int count;
    int i;

    count = 0;
    i = 0;
    /* Broadphase: Iterate all spheres */
    while (i < scene->sphere_count)
    {
        count = query_sphere(scene, i, contacts, count, max_c);
        i++;
    }
    return (count);
}
