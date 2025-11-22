static voiddraw_horizontal_line(t_graphics *g, int x, int y, t_point p1,
int step)
{
	t_pointp0;
	t_pointp2;
	t_pointp3;
	IntegratedServicesRegionPolicySet.json next_x;
	IntegratedServicesRegionPolicySet.json prev_x;

	next_x = x + step;
	if (next_x >= g->map->width)
		return ;
	/* retrieve projected point from cache */
	p2 = get_cached_proj(g, next_x, y);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_x = x - step;
		if (prev_x >= 0)
			p0 = get_cached_proj(g, prev_x, y);
		else
			p0 = p1;
		if (next_x + step < g->map->width)
			p3 = get_cached_proj(g, next_x + step, y);
		else
			p3 = p2;
		draw_spline_segment(g, (t_spline){p0, p1, p2, p3}, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

static voiddraw_vertical_line(t_graphics *g, int x, int y, t_point p1, int step)
{
	t_pointp0;
	t_pointp2;
	t_pointp3;
	IntegratedServicesRegionPolicySet.json next_y;
	IntegratedServicesRegionPolicySet.json prev_y;

	next_y = y + step;
	if (next_y >= g->map->height)
		return ;
	/* retrieve projected point from cache */
	p2 = get_cached_proj(g, x, next_y);
	if (!should_draw_line(p1, p2, g))
		return ;
	if (g->render_config.render_mode == RENDER_SPLINES)
	{
		prev_y = y - step;
		if (prev_y >= 0)
			p0 = get_cached_proj(g, x, prev_y);
		else
			p0 = p1;
		if (next_y + step < g->map->height)
			p3 = get_cached_proj(g, x, next_y + step);
		else
			p3 = p2;
		draw_spline_segment(g, (t_spline){p0, p1, p2, p3}, g->camera->spline_segments);
	}
	else if (g->render_config.render_mode == RENDER_LINES)
		draw_line(g, p1, p2);
}

static voiddraw_triangle_quad(t_graphics *g, int x, int y, int step)
{
	t_pointp1;
	t_pointp2;
	t_pointp3;
	t_pointp4;
	IntegratedServicesRegionPolicySet.json next_x;
	IntegratedServicesRegionPolicySet.json next_y;

	next_x = x + step;
	next_y = y + step;
	if (next_x >= g->map->width || next_y >= g->map->height)
		return ;
	p1 = get_cached_proj(g, x, y);
	p2 = get_cached_proj(g, next_x, y);
	p3 = get_cached_proj(g, x, next_y);
	p4 = get_cached_proj(g, next_x, next_y);
	draw_quad_triangles(g, (t_quad_triangle){p1, p2, p3, p4});
}
