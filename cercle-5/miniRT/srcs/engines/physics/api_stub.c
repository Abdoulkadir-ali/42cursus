/* Minimal physics API stubs to enable incremental migration.
 * These provide small, safe defaults and are intended to be replaced
 * by the full physics implementation during the refactor.
 */

#include "physics.h"
#include <stdlib.h>
#include <string.h>

t_physics *phys_create(struct s_scene *scene)
{
    t_physics *p = malloc(sizeof(*p));
    if (!p)
        return NULL;
    memset(p, 0, sizeof(*p));
    p->scene = scene;
    p->gravity = (t_vec3){0.0, -9.81, 0.0};
#ifdef GLOBAL_DAMPING
    p->damping = GLOBAL_DAMPING;
#else
    p->damping = 0.12;
#endif
    p->fixed_dt = 1.0 / 60.0;
    p->solver_iters = SOLVER_ITERATIONS;
    p->needs_bake = true;
    p->pool = NULL;
    return p;
}

void phys_destroy(t_physics *phys)
{
    if (!phys)
        return;
    /* TODO: free pool and related resources when implemented */
    free(phys);
}

void phys_bake_scene(t_physics *phys, t_scene *scene)
{
    if (!phys || !scene)
        return;
    /* Minimal bake: associate scene pointer. Full implementation will
     * populate phys->bodies[] pool and DBVT leaves.
     */
    phys->scene = scene;
    phys->needs_bake = false;
}

void phys_step(t_physics *phys, t_scene *scene, double dt)
{
    (void)scene;
    if (!phys)
        return;
    /* Minimal step: nothing for now. Full implementation will integrate
     * bodies, run broadphase/narrowphase and apply constraints.
     */
    (void)dt;
}
