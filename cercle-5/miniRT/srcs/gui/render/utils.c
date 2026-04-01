#include "functions/gui/render.h"
#include "public/engines.h"

void make_camera_ray(t_render *render, double x, double y, t_ray *ray)
{
	double px;
	double py;
	t_vec3 dir;

	px = (2.0 * (x + 0.5) / render->gui->win.size.x - 1.0)
		* render->half_width * render->aspect_ratio;
	py = (1.0 - 2.0 * (y + 0.5) / render->gui->win.size.y)
		* render->half_height * render->aspect_ratio;
	dir = vec3_norm(vec3_add(render->transform.forward,
				vec3_add(vec3_scale(render->transform.right, px),
					vec3_scale(render->transform.up, py))));
	ray_init(ray, render->transform.pos, dir);
}
