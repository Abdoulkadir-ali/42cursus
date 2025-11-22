/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/22 05:02:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

/* Helper struct for edge walking */
typedef struct s_edge {
	double x;
	double z;
	double r, g, b;
	double dx; /* Slope X */
	double dz; /* Slope Z */
	double dr, dg, db; /* Slope Colors */
} t_edge;

static void setup_edge(t_edge *e, t_point top, t_point bot)
{
	int height = (int)bot.pos.y - (int)top.pos.y;
	if (height <= 0) return;

	double inv_h = 1.0 / height;
	
	/* Initial values */
	e->x = top.pos.x;
	e->z = top.pos.z;
	e->r = get_red(top.color);
	e->g = get_green(top.color);
	e->b = get_blue(top.color);

	/* Gradients (How much to add per Y step) */
	e->dx = (bot.pos.x - top.pos.x) * inv_h;
	e->dz = (bot.pos.z - top.pos.z) * inv_h;
	e->dr = (get_red(bot.color) - e->r) * inv_h;
	e->dg = (get_green(bot.color) - e->g) * inv_h;
	e->db = (get_blue(bot.color) - e->b) * inv_h;
}

static void step_edge(t_edge *e)
{
	e->x += e->dx;
	e->z += e->dz;
	e->r += e->dr;
	e->g += e->dg;
	e->b += e->db;
}

static void swap_points(t_point *a, t_point *b) { t_point t = *a; *a = *b; *b = t; }

static void rasterize_flat_bottom(t_graphics *g, t_point top, t_point b1, t_point b2)
{
	t_edge e1, e2;
	int y_start = (int)top.pos.y;
	int y_end = (int)b1.pos.y;
	t_scanline_data data;

	setup_edge(&e1, top, b1);
	setup_edge(&e2, top, b2);

	/* Correct for off-screen start */
	if (y_start < 0) {
		int skip = -y_start;
		for(int k=0; k<skip; k++) { step_edge(&e1); step_edge(&e2); }
		y_start = 0;
	}

	for (int y = y_start; y < y_end; y++)
	{
		if (y >= g->window->height) break;
		
		data.y = y;
		data.x1 = (int)e1.x;
		data.x2 = (int)e2.x;
		data.z1 = (float)e1.z;
		data.z2 = (float)e2.z;
		data.c1 = create_color((int)e1.r, (int)e1.g, (int)e1.b);
		data.c2 = create_color((int)e2.r, (int)e2.g, (int)e2.b);
		
		draw_horizontal_scanline_z(g, data);
		
		step_edge(&e1);
		step_edge(&e2);
	}
}

static void rasterize_flat_top(t_graphics *g, t_point t1, t_point t2, t_point bot)
{
	t_edge e1, e2;
	int y_start = (int)t1.pos.y;
	int y_end = (int)bot.pos.y;
	t_scanline_data data;

	setup_edge(&e1, t1, bot);
	setup_edge(&e2, t2, bot);

	if (y_start < 0) {
		int skip = -y_start;
		for(int k=0; k<skip; k++) { step_edge(&e1); step_edge(&e2); }
		y_start = 0;
	}

	for (int y = y_start; y < y_end; y++)
	{
		if (y >= g->window->height) break;

		data.y = y;
		data.x1 = (int)e1.x;
		data.x2 = (int)e2.x;
		data.z1 = (float)e1.z;
		data.z2 = (float)e2.z;
		data.c1 = create_color((int)e1.r, (int)e1.g, (int)e1.b);
		data.c2 = create_color((int)e2.r, (int)e2.g, (int)e2.b);

		draw_horizontal_scanline_z(g, data);

		step_edge(&e1);
		step_edge(&e2);
	}
}

void draw_filled_triangle(t_graphics *g, t_triangle t)
{
	/* 1. Sort vertices by Y */
	if (t.p1.pos.y > t.p2.pos.y) swap_points(&t.p1, &t.p2);
	if (t.p1.pos.y > t.p3.pos.y) swap_points(&t.p1, &t.p3);
	if (t.p2.pos.y > t.p3.pos.y) swap_points(&t.p2, &t.p3);

	/* 2. Split into flat-bottom and flat-top */
	if ((int)t.p2.pos.y == (int)t.p3.pos.y)
	{
		rasterize_flat_bottom(g, t.p1, t.p2, t.p3);
	}
	else if ((int)t.p1.pos.y == (int)t.p2.pos.y)
	{
		rasterize_flat_top(g, t.p1, t.p2, t.p3);
	}
	else
	{
		/* Split the triangle */
		t_point p4;
		double ratio = (t.p2.pos.y - t.p1.pos.y) / (t.p3.pos.y - t.p1.pos.y);
		
		p4.pos.x = t.p1.pos.x + (t.p3.pos.x - t.p1.pos.x) * ratio;
		p4.pos.y = t.p2.pos.y;
		p4.pos.z = t.p1.pos.z + (t.p3.pos.z - t.p1.pos.z) * ratio;
		p4.color = interpolate_color(t.p1.color, t.p3.color, ratio);

		rasterize_flat_bottom(g, t.p1, t.p2, p4);
		rasterize_flat_top(g, t.p2, p4, t.p3);
	}
}

/* Keep wireframe logic same */
void	draw_wireframe_triangle(t_graphics *g, t_triangle t)
{
	draw_line(g, t.p1, t.p2);
	draw_line(g, t.p2, t.p3);
	draw_line(g, t.p3, t.p1);
}

void	draw_quad_triangles(t_graphics *g, t_quad_triangle quad)
{
	if (g->render_config.fill_triangles)
	{
		draw_filled_triangle(g, (t_triangle){quad.p1, quad.p2, quad.p3});
		draw_filled_triangle(g, (t_triangle){quad.p2, quad.p4, quad.p3});
	}
	else
	{
		draw_wireframe_triangle(g, (t_triangle){quad.p1, quad.p2, quad.p3});
		draw_wireframe_triangle(g, (t_triangle){quad.p2, quad.p4, quad.p3});
	}
}