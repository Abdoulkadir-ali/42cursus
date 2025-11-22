/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 03:58:29 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 04:46:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "color.h"
#include "graphics.h"
#include <math.h>

/* Fixed Point Scale: 2^16 = 65536 */
#define FP_SHIFT 16

static void	draw_pixel_fast(t_graphics *g, t_pixel_draw_params p)
{
	/* Z-Buffer Check:
	   We cast the pointer to int* for atomic-like integer comparison if possible,
	   but standard float comparison is fine here given memory bandwidth is the limit.
	*/
	if (!g->render_config.use_depth_culling || !p.z_addr || p.zr < *p.z_addr)
	{
		if (g->render_config.use_depth_culling && p.z_addr)
			*p.z_addr = p.zr;
		*(unsigned int *)p.pixel_addr = p.color;
	}
}

static void	draw_pixel_fast_no_z(t_pixel_draw_params p)
{
	*(unsigned int *)p.pixel_addr = p.color;
}

static void	bresenham_fixed(t_graphics *g, t_bresenham_params p)
{
	int		err;
	int		e2;
	t_vec2	current;
	int		color;
	
	/* --- FIXED POINT SETUP --- */
	/* Convert start values and steps to scaled integers */
	int		fp_r = (int)(p.r * (1 << FP_SHIFT));
	int		fp_g = (int)(p.green * (1 << FP_SHIFT));
	int		fp_b = (int)(p.b * (1 << FP_SHIFT));
	int		fp_dr = (int)(p.dr * (1 << FP_SHIFT));
	int		fp_dg = (int)(p.dg * (1 << FP_SHIFT));
	int		fp_db = (int)(p.db * (1 << FP_SHIFT));

	/* We keep Z as float for precision in the buffer, but could fix-point it too.
	   For now, color is the main CPU hog due to 3 components. */
	
	t_pixel_draw_params	pdp;
	pdp.pixel_addr = p.pixel_addr;
	pdp.z_addr = p.z_addr;

	err = (int)p.delta.x - (int)p.delta.y;
	current = p.start;

	while (1)
	{
		/* BIT SHIFT to get actual integer color values (Fast!) */
		color = create_color(fp_r >> FP_SHIFT, fp_g >> FP_SHIFT, fp_b >> FP_SHIFT);

		/* No color shift applied */

		/* Draw */
		pdp.pixel_addr = p.pixel_addr;
		pdp.z_addr = p.z_addr;
		pdp.zr = (float)p.zr;
		pdp.color = color;
		draw_pixel_fast(g, pdp);

		/* Loop Break */
		if (current.x == p.end.x && current.y == p.end.y)
			break;

		/* Error Correction & Pointer Walking */
		e2 = 2 * err;
		if (e2 > -p.delta.y)
		{
			err -= p.delta.y;
			current.x += p.sign.x;
			if (current.x < 0 || current.x >= p.ctx.width) break;
			p.pixel_addr += p.ctx.step_x;
			if (p.z_addr) p.z_addr += p.ctx.z_step_x;
		}
		if (e2 < p.delta.x)
		{
			err += p.delta.x;
			current.y += p.sign.y;
			if (current.y < 0 || current.y >= p.ctx.height) break;
			p.pixel_addr += p.ctx.step_y;
			if (p.z_addr) p.z_addr += p.ctx.z_step_y;
		}

		/* Increment Interpolators (Integer Addition) */
		p.zr += p.z_step_val; /* Keep Z as float for buffer compatibility */
		fp_r += fp_dr;
		fp_g += fp_dg;
		fp_b += fp_db;
	}
}

static void	bresenham_fixed_shifted(t_graphics *g, t_bresenham_params p)
{
	int		err;
	int		e2;
	t_vec2	current;
	int		color;
	
	/* --- FIXED POINT SETUP --- */
	/* Convert start values and steps to scaled integers */
	int		fp_r = (int)(p.r * (1 << FP_SHIFT));
	int		fp_g = (int)(p.green * (1 << FP_SHIFT));
	int		fp_b = (int)(p.b * (1 << FP_SHIFT));
	int		fp_dr = (int)(p.dr * (1 << FP_SHIFT));
	int		fp_dg = (int)(p.dg * (1 << FP_SHIFT));
	int		fp_db = (int)(p.db * (1 << FP_SHIFT));

	/* We keep Z as float for precision in the buffer, but could fix-point it too.
	   For now, color is the main CPU hog due to 3 components. */
	
	t_pixel_draw_params	pdp;
	pdp.pixel_addr = p.pixel_addr;
	pdp.z_addr = p.z_addr;

	err = (int)p.delta.x - (int)p.delta.y;
	current = p.start;

	while (1)
	{
		/* BIT SHIFT to get actual integer color values (Fast!) */
		color = create_color(fp_r >> FP_SHIFT, fp_g >> FP_SHIFT, fp_b >> FP_SHIFT);

		/* Always apply color shift */
		color = shift_color(color, g->camera->color_shift.x, 
				g->camera->color_shift.y, g->camera->color_shift.z);

		/* Draw */
		pdp.pixel_addr = p.pixel_addr;
		pdp.z_addr = p.z_addr;
		pdp.zr = (float)p.zr;
		pdp.color = color;
		draw_pixel_fast(g, pdp);

		/* Loop Break */
		if (current.x == p.end.x && current.y == p.end.y)
			break;

		/* Error Correction & Pointer Walking */
		e2 = 2 * err;
		if (e2 > -p.delta.y)
		{
			err -= p.delta.y;
			current.x += p.sign.x;
			if (current.x < 0 || current.x >= p.ctx.width) break;
			p.pixel_addr += p.ctx.step_x;
			if (p.z_addr) p.z_addr += p.ctx.z_step_x;
		}
		if (e2 < p.delta.x)
		{
			err += p.delta.x;
			current.y += p.sign.y;
			if (current.y < 0 || current.y >= p.ctx.height) break;
			p.pixel_addr += p.ctx.step_y;
			if (p.z_addr) p.z_addr += p.ctx.z_step_y;
		}

		/* Increment Interpolators (Integer Addition) */
		p.zr += p.z_step_val; /* Keep Z as float for buffer compatibility */
		fp_r += fp_dr;
		fp_g += fp_dg;
		fp_b += fp_db;
	}
}

static void	bresenham_fixed_no_z(t_bresenham_params p)
{
	int		err;
	int		e2;
	t_vec2	current;
	int		color;
	
	/* --- FIXED POINT SETUP --- */
	/* Convert start values and steps to scaled integers */
	int		fp_r = (int)(p.r * (1 << FP_SHIFT));
	int		fp_g = (int)(p.green * (1 << FP_SHIFT));
	int		fp_b = (int)(p.b * (1 << FP_SHIFT));
	int		fp_dr = (int)(p.dr * (1 << FP_SHIFT));
	int		fp_dg = (int)(p.dg * (1 << FP_SHIFT));
	int		fp_db = (int)(p.db * (1 << FP_SHIFT));

	/* We keep Z as float for precision in the buffer, but could fix-point it too.
	   For now, color is the main CPU hog due to 3 components. */
	
	t_pixel_draw_params	pdp;
	pdp.pixel_addr = p.pixel_addr;

	err = (int)p.delta.x - (int)p.delta.y;
	current = p.start;

	while (1)
	{
		/* BIT SHIFT to get actual integer color values (Fast!) */
		color = create_color(fp_r >> FP_SHIFT, fp_g >> FP_SHIFT, fp_b >> FP_SHIFT);

		/* No color shift applied */

		/* Draw */
		pdp.pixel_addr = p.pixel_addr;
		pdp.color = color;
		draw_pixel_fast_no_z(pdp);

		/* Loop Break */
		if (current.x == p.end.x && current.y == p.end.y)
			break;

		/* Error Correction & Pointer Walking */
		e2 = 2 * err;
		if (e2 > -p.delta.y)
		{
			err -= p.delta.y;
			current.x += p.sign.x;
			if (current.x < 0 || current.x >= p.ctx.width) break;
			p.pixel_addr += p.ctx.step_x;
		}
		if (e2 < p.delta.x)
		{
			err += p.delta.x;
			current.y += p.sign.y;
			if (current.y < 0 || current.y >= p.ctx.height) break;
			p.pixel_addr += p.ctx.step_y;
		}

		/* Increment Interpolators (Integer Addition) */
		p.zr += p.z_step_val; /* Keep Z as float for buffer compatibility */
		fp_r += fp_dr;
		fp_g += fp_dg;
		fp_b += fp_db;
	}
}

static void	bresenham_fixed_no_z_shifted(t_graphics *g, t_bresenham_params p)
{
	int		err;
	int		e2;
	t_vec2	current;
	int		color;
	
	/* --- FIXED POINT SETUP --- */
	/* Convert start values and steps to scaled integers */
	int		fp_r = (int)(p.r * (1 << FP_SHIFT));
	int		fp_g = (int)(p.green * (1 << FP_SHIFT));
	int		fp_b = (int)(p.b * (1 << FP_SHIFT));
	int		fp_dr = (int)(p.dr * (1 << FP_SHIFT));
	int		fp_dg = (int)(p.dg * (1 << FP_SHIFT));
	int		fp_db = (int)(p.db * (1 << FP_SHIFT));

	/* We keep Z as float for precision in the buffer, but could fix-point it too.
	   For now, color is the main CPU hog due to 3 components. */
	
	t_pixel_draw_params	pdp;
	pdp.pixel_addr = p.pixel_addr;

	err = (int)p.delta.x - (int)p.delta.y;
	current = p.start;

	while (1)
	{
		/* BIT SHIFT to get actual integer color values (Fast!) */
		color = create_color(fp_r >> FP_SHIFT, fp_g >> FP_SHIFT, fp_b >> FP_SHIFT);

		/* Always apply color shift */
		color = shift_color(color, g->camera->color_shift.x, 
				g->camera->color_shift.y, g->camera->color_shift.z);

		/* Draw */
		pdp.pixel_addr = p.pixel_addr;
		pdp.color = color;
		draw_pixel_fast_no_z(pdp);

		/* Loop Break */
		if (current.x == p.end.x && current.y == p.end.y)
			break;

		/* Error Correction & Pointer Walking */
		e2 = 2 * err;
		if (e2 > -p.delta.y)
		{
			err -= p.delta.y;
			current.x += p.sign.x;
			if (current.x < 0 || current.x >= p.ctx.width) break;
			p.pixel_addr += p.ctx.step_x;
		}
		if (e2 < p.delta.x)
		{
			err += p.delta.x;
			current.y += p.sign.y;
			if (current.y < 0 || current.y >= p.ctx.height) break;
			p.pixel_addr += p.ctx.step_y;
		}

		/* Increment Interpolators (Integer Addition) */
		p.zr += p.z_step_val; /* Keep Z as float for buffer compatibility */
		fp_r += fp_dr;
		fp_g += fp_dg;
		fp_b += fp_db;
	}
}

void	draw_line(t_graphics *g, t_point start, t_point end)
{
	t_draw_line_ctx	dlc;

	if (!init_draw_line_ctx(g, start, end, &dlc))
		return ;
	
	/* Pass data to the fixed-point loop */
	dlc.p.start = dlc.start_pos;
	dlc.p.end = dlc.end_pos;
	dlc.p.delta = dlc.delta;
	dlc.p.sign = dlc.sign;
	dlc.p.ctx = dlc.ctx;
	dlc.p.pixel_addr = dlc.pixel_addr;
	dlc.p.z_addr = dlc.z_addr;
	
	/* Interpolation data */
	dlc.p.zr = dlc.interp.zr;
	dlc.p.z_step_val = dlc.interp.z_step_val;
	dlc.p.r = dlc.interp.r;
	dlc.p.green = dlc.interp.green;
	dlc.p.b = dlc.interp.b;
	dlc.p.dr = dlc.interp.dr;
	dlc.p.dg = dlc.interp.dg;
	dlc.p.db = dlc.interp.db;

	if (g->render_config.use_depth_culling)
	{
		if (g->camera->color_shift.x || g->camera->color_shift.y || g->camera->color_shift.z)
			bresenham_fixed_shifted(g, dlc.p);
		else
			bresenham_fixed(g, dlc.p);
	}
	else
	{
		if (g->camera->color_shift.x || g->camera->color_shift.y || g->camera->color_shift.z)
			bresenham_fixed_no_z_shifted(g, dlc.p);
		else
			bresenham_fixed_no_z(dlc.p);
	}
}