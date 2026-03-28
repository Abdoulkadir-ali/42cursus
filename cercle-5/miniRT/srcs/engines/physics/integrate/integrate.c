#include "physics.h"

static void	integrate_soa_body(t_scene *scene, int i, double dt)
{
	t_physics_soa		*p = scene->physics->soa;
	t_primitive_array	*gm = &scene->primitives;
	int					idx = p->prim_idx[i];
	t_vec3				g;

	g = gravity_vec();
	/* HOT Physics Integration */
	p->hot.vx[i] += (float)(g.x * dt);
	p->hot.vy[i] += (float)(g.y * dt);
	p->hot.vz[i] += (float)(g.z * dt);
	p->hot.vx[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->hot.vy[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->hot.vz[i] *= (float)pow(1.0 - GLOBAL_DAMPING, dt);
	p->hot.ang_vx[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	p->hot.ang_vy[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);
	p->hot.ang_vz[i] *= (float)pow(1.0 - GLOBAL_DAMPING * 0.5, dt);

	/* Writeback to Geometry */
	gm->px[idx] += p->hot.vx[i] * (float)dt;
	gm->py[idx] += p->hot.vy[i] * (float)dt;
	gm->pz[idx] += p->hot.vz[i] * (float)dt;
	gm->ax[idx] += p->hot.ang_vx[i] * (float)(dt * (180.0 / M_PI));
	gm->ay[idx] += p->hot.ang_vy[i] * (float)(dt * (180.0 / M_PI));
	gm->az[idx] += p->hot.ang_vz[i] * (float)(dt * (180.0 / M_PI));
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

