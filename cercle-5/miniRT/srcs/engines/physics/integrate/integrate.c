#include "physics.h"

static void	integrate_soa_body(t_physics *phys, int i, double dt)
{
	t_physics_soa		*p;
	t_primitive_array	*gm;
	int					idx;
	t_vec3				g;

	p = phys->soa;
	gm = &phys->scene->primitives;
	idx = p->prim_idx[i];
	g = gravity_vec();
	p->hot.vx[i] += (float)(g.x * dt);
	p->hot.vy[i] += (float)(g.y * dt);
	p->hot.vz[i] += (float)(g.z * dt);
	p->hot.vx[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->hot.vy[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->hot.vz[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->hot.ang_vx[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	p->hot.ang_vy[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	p->hot.ang_vz[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	gm->px[idx] += p->hot.vx[i] * (float)dt;
	gm->py[idx] += p->hot.vy[i] * (float)dt;
	gm->pz[idx] += p->hot.vz[i] * (float)dt;
	gm->ax[idx] += p->hot.ang_vx[i] * (float)(dt * (180.0 / M_PI));
	gm->ay[idx] += p->hot.ang_vy[i] * (float)(dt * (180.0 / M_PI));
	gm->az[idx] += p->hot.ang_vz[i] * (float)(dt * (180.0 / M_PI));
}

void	integrate_bodies(t_physics *phys, double dt)
{
	size_t	i;

	i = 0;
	if (!phys->soa)
		return ;
	while (i < phys->soa->count)
	{
		integrate_soa_body(phys, (int)i, dt);
		i++;
	}
}

