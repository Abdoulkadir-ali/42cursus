#include "raytracing.h"

t_vec3 sample_texture_pool(t_shading *sha, int idx, double u, double v)
{
	unsigned char *pix;
	t_vec2i d;
	int x, y, p;
	t_rt_engine *rt;

	rt = (t_rt_engine *)sha->rt;
	if (idx < 0 || !rt->texture_pool || !rt->texture_pool[idx])
		return (vec3(1, 0, 1));
	d = rt->texture_dims[idx];
	x = (int)(u * (double)d.x) % d.x;
	y = (int)(v * (double)d.y) % d.y;
	if (x < 0) x += d.x;
	if (y < 0) y += d.y;
	p = (y * d.x + x) * 4;
	pix = rt->texture_pool[idx];
	return (vec3(pix[p] / 255.0, pix[p + 1] / 255.0, pix[p + 2] / 255.0));
}
