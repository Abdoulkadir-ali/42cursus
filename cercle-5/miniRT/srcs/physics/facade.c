/* Minimal physics facade: create/bake/step t_physics on demand for a scene.
 * This file keeps the association between `t_scene*` and `t_physics*` local
 * to the physics implementation so `scene.h` does not need to embed physics.
 */

#include "physics.h"
#include "debug.h"
#include <stdlib.h>

struct s_scene_phys_map
{
    t_scene *scene;
    t_physics *phys;
    struct s_scene_phys_map *next;
};

static struct s_scene_phys_map *g_map_head = NULL;

static t_physics *get_mapped_phys(t_scene *scene)
{
    struct s_scene_phys_map *it = g_map_head;

    while (it)
    {
        if (it->scene == scene)
            return it->phys;
        it = it->next;
    }
    return NULL;
}

static void map_phys(t_scene *scene, t_physics *phys)
{
    struct s_scene_phys_map *n = malloc(sizeof(*n));
    if (!n)
        return;
    n->scene = scene;
    n->phys = phys;
    n->next = g_map_head;
    g_map_head = n;
}

void simulate_physics(t_scene *scene, double dt)
{
    t_physics *phys = get_mapped_phys(scene);

    if (!phys)
    {
        phys = phys_create(scene);
        if (!phys)
            return;
        /* Bake scene bodies into phys (implementation detail) */
        /* phys_bake_scene may be implemented by the physics core; call if present */
#ifdef HAVE_PHYS_BAKE
        phys_bake_scene(phys, scene);
#endif
        map_phys(scene, phys);
    }

    /* Prefer phys_step if available, otherwise call simulate wrapper */
#ifdef HAVE_PHYS_STEP
    phys_step(phys, scene, dt);
#else
    /* Fallback: if library provides simulate_physics(t_physics*,dt) use it */
    simulate_physics(phys, dt);
#endif
}

void update_physics_settings(t_physics *phys, const t_physics_settings *s)
{
    if (!phys || !s)
        return;
    phys->damping = s->damping;
    phys->solver_iters = s->solver_iters;
    phys->fixed_dt = s->fixed_dt;
    phys->gravity = s->gravity;
}

void get_physics_settings(const t_physics *phys, t_physics_settings *out)
{
    if (!phys || !out)
        return;
    out->damping = phys->damping;
    out->solver_iters = phys->solver_iters;
    out->fixed_dt = phys->fixed_dt;
    out->gravity = phys->gravity;
}
