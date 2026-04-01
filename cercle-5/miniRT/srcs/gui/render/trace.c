#include "functions/gui/render.h"
#include "public/engines.h"
#include <stdint.h>

static int pack_color(t_vec3 color)
{
	int r = ((int)color.x & 0xFF) << 16;
	int g = ((int)color.y & 0xFF) << 8;
	int b = (int)color.z & 0xFF;
	return (r | g | b);
}

static void fill_block(t_render *render)
{
	t_vec2i d;
	uint32_t *dst;

	d.y = 0;
	while (d.y < render->step && (render->pos.y + d.y) < render->gui->win.size.y)
	{
		dst = (uint32_t *)(render->pixel_addr + (d.y * render->gui->win.line_len));
		d.x = 0;
		while (d.x < render->step && (render->pos.x + d.x) < render->gui->win.size.x)
		{
			dst[d.x] = render->color;
			d.x++;
		}
		d.y++;
	}
}

void process_pixel(t_render *render, t_vec2i pos, char *pixel_addr)
{
	t_ray ray;
	t_vec3 color;
	uint32_t *dst;

	make_camera_ray(render, (double)pos.x, (double)pos.y, &ray);
	color = trace_ray(render->gui->scene->bvh, &ray, render->gui->scene);
	render->pos = pos;
	render->color = pack_color(color);
	render->pixel_addr = pixel_addr;
	if (render->step > 1)
		fill_block(render);
	else
	{
		dst = (uint32_t *)render->pixel_addr;
		*dst = render->color;
	}
}
