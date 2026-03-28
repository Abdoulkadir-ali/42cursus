#include "physics.h"

static void	integrate_soa_body(t_scene *scene, int i, double dt)
{
	t_physics_soa		*p = scene->physics->soa;
	t_primitive_array	*gm = &scene->primitives;
	int					idx = p->prim_idx[i];
	t_vec3				g;

	g = gravity_vec();
	/* HOT Physics Integration */
	p->vx[i] += (float)(g.x * dt);
	p->vy[i] += (float)(g.y * dt);
	p->vz[i] += (float)(g.z * dt);
	p->vx[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->vy[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->vz[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->ang_vx[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	p->ang_vy[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	p->ang_vz[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);

	/* Writeback to Geometry */
	gm->px[idx] += p->vx[i] * (float)dt;
	gm->py[idx] += p->vy[i] * (float)dt;
	gm->pz[idx] += p->vz[i] * (float)dt;
	gm->ax[idx] += p->ang_vx[i] * (float)(dt * (180.0 / M_PI));
	gm->ay[idx] += p->ang_vy[i] * (float)(dt * (180.0 / M_PI));
	gm->az[idx] += p->ang_vz[i] * (float)(dt * (180.0 / M_PI));
}

void	integrate_bodies(t_scene *scene, double dt)
{
	size_t	i;

	i = 0;
	if (!scene->physics->soa)
		return ;
	while (i < scene->physics->soa->count)
	{
		integrate_soa_body(scene, (int)i, dt);
		i++;
	}
}

