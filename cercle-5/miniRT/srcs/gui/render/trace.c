/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:31:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/06 20:31:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	pack_color(t_vec3 color)
{
	int	r;
	int	g;
	int	b;

	r = ((int)color.x & 0xFF) << 16;
	g = ((int)color.y & 0xFF) << 8;
	b = (int)color.z & 0xFF;
	return (r | g | b);
}

static void	fill_block(t_render *render)
{
	int		dx;
	int		dy;
	uint32_t	*dst;

	dy = 0;
	while (dy < render->step && (render->pos.y + dy) < render->gui->win.height)
	{
		dst = (uint32_t *)(render->pixel_addr + (dy * render->gui->win.line_len));
		dx = 0;
		while (dx < render->step && (render->pos.x + dx) < render->gui->win.width)
		{
			dst[dx] = render->color;
			dx++;
		}
		dy++;
	}
}

void	process_pixel(t_render *render, t_vec2i pos, char *pixel_addr)
{
	t_ray			ray;
	t_vec3			color;
	uint32_t		*dst;

	make_camera_ray(render, pos.x, pos.y, &ray);
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
