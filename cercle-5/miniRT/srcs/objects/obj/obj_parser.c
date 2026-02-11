/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/08 14:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "debug.h"

static void	obj_parse_v(t_obj_ctx *ctx, t_parser *p)
{
	t_vec3	v;

	v.w = 1.0;
	v.x = parse_double(p);
	parser_skip_whitespace(p);
	v.y = parse_double(p);
	parser_skip_whitespace(p);
	v.z = parse_double(p);
	
	if (!dynarray_ensure((void **)&ctx->temp_v, ctx->v_count, &ctx->v_cap, sizeof(t_vec3)))
		return ;
	ctx->temp_v[ctx->v_count++] = v;
	aabb_expand_point(&ctx->bbox, v);
}

static void	obj_parse_vt(t_obj_ctx *ctx, t_parser *p)
{
	t_vec2	vt;

	vt.x = parse_double(p);
	parser_skip_whitespace(p);
	vt.y = parse_double(p);
	
	if (!dynarray_ensure((void **)&ctx->temp_vt, ctx->vt_count, &ctx->vt_cap, sizeof(t_vec2)))
		return ;
	ctx->temp_vt[ctx->vt_count++] = vt;
}

static void	obj_parse_vn(t_obj_ctx *ctx, t_parser *p)
{
	t_vec3	vn;

	vn.w = 0.0;
	vn.x = parse_double(p);
	parser_skip_whitespace(p);
	vn.y = parse_double(p);
	parser_skip_whitespace(p);
	vn.z = parse_double(p);
	
	if (!dynarray_ensure((void **)&ctx->temp_vn, ctx->vn_count, &ctx->vn_cap, sizeof(t_vec3)))
		return ;
	ctx->temp_vn[ctx->vn_count++] = vn;
}

static void	ensure_out_capacity(t_obj_ctx *ctx)
{
	size_t	new_cap;
	t_vec3	*nv;
	t_vec3	*nn;
	t_vec2	*nt;

	if (ctx->out_v_count < ctx->out_v_cap)
		return ;
	new_cap = ctx->out_v_cap == 0 ? 1024 : ctx->out_v_cap * 2;
	nv = realloc(ctx->out_v, new_cap * sizeof(t_vec3));
	nn = realloc(ctx->out_vn, new_cap * sizeof(t_vec3));
	nt = realloc(ctx->out_vt, new_cap * sizeof(t_vec2));
	if (!nv || !nn || !nt) return ; /* Error handling simplified */
	ctx->out_v = nv;
	ctx->out_vn = nn;
	ctx->out_vt = nt;
	ctx->out_v_cap = new_cap;
}

static void	add_vert(t_obj_ctx *ctx, int vi, int vti, int vni)
{
	ensure_out_capacity(ctx);
	
	/* Indices are 1-based, or negative */
	if (vi < 0) vi = ctx->v_count + vi; else vi--;
	if (vti < 0) vti = ctx->vt_count + vti; else vti--;
	if (vni < 0) vni = ctx->vn_count + vni; else vni--;

	if (vi >= 0 && vi < (int)ctx->v_count)
		ctx->out_v[ctx->out_v_count] = ctx->temp_v[vi];
	if (vti >= 0 && vti < (int)ctx->vt_count)
		ctx->out_vt[ctx->out_v_count] = ctx->temp_vt[vti];
	else
		ctx->out_vt[ctx->out_v_count] = (t_vec2){0, 0};
	if (vni >= 0 && vni < (int)ctx->vn_count)
		ctx->out_vn[ctx->out_v_count] = ctx->temp_vn[vni];
	else
		ctx->out_vn[ctx->out_v_count] = (t_vec3){0, 1, 0, 0};

	if (!dynarray_ensure((void **)&ctx->out_i, ctx->out_i_count, &ctx->out_i_cap, sizeof(int)))
		return ;
	ctx->out_i[ctx->out_i_count++] = ctx->out_v_count++;
}

static void	obj_parse_f(t_obj_ctx *ctx, t_parser *p)
{
	int		vi[32], vti[32], vni[32];
	int		count = 0;
	char	c;

	while (count < 32)
	{
		parser_skip_whitespace(p);
		c = parser_peek(p);
		if (!c || c == '\n') break;
		
		vi[count] = parse_int(p);
		vti[count] = 0; vni[count] = 0;
		if (parser_peek(p) == '/')
		{
			parser_advance(p);
			if (parser_peek(p) != '/') vti[count] = parse_int(p);
			if (parser_peek(p) == '/')
			{
				parser_advance(p);
				vni[count] = parse_int(p);
			}
		}
		count++;
	}
	
	/* Triangulate fan */
	for (int i = 1; i < count - 1; i++)
	{
		add_vert(ctx, vi[0], vti[0], vni[0]);
		add_vert(ctx, vi[i], vti[i], vni[i]);
		add_vert(ctx, vi[i+1], vti[i+1], vni[i+1]);
	}
	if (count > 0)
		ft_print_debug("DEBUG: Parsed face with %d vertices -> %d triangles\n", count, count - 2);
}

static void	obj_parse_mtllib(t_obj_ctx *ctx, t_parser *p, t_scene *scene, const char *obj_path)
{
	char	name[256];
	char	*dir;
	char	*full;
	int		i = 0;

	parser_skip_whitespace(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;

	dir = path_get_dir(obj_path);
	full = dir ? ft_strjoin(dir, name) : ft_strdup(name);
	if (dir) free(dir);
	
	parse_mtl(scene, full);
	free(full);
	(void)ctx;
}

static void	obj_parse_usemtl(t_obj_ctx *ctx, t_parser *p, t_scene *scene)
{
	char	name[256];
	int		i = 0;

	parser_skip_whitespace(p);
	while (i < 255 && parser_peek(p) && !ft_isspace(parser_peek(p)))
	{
		name[i++] = parser_peek(p);
		parser_advance(p);
	}
	name[i] = 0;

	ctx->current_mat_id = scene_find_material(scene, name);
}

bool	parse_obj(const char *path, t_scene *scene)
{
	t_parser	p;
	t_obj_ctx	ctx;
	int			fd;
	char		id[16];

	ft_memset(&ctx, 0, sizeof(t_obj_ctx));
	ctx.current_mat_id = -1;
	ctx.bbox = aabb_create_empty();
	if ((fd = open(path, O_RDONLY)) < 0) return (false);
	parser_init(&p, fd);
	ft_print_debug("DEBUG: Starting parse of OBJ: %s\n", path);

	while (true)
	{
		parser_skip_whitespace(&p);
		if (p.eof && p.cursor >= p.bytes_read) break;
		if (parser_peek(&p) == '#') { while (parser_peek(&p) && parser_peek(&p) != '\n') parser_advance(&p); continue; }
		
		int i = 0;
		while (i < 15 && parser_peek(&p) && !ft_isspace(parser_peek(&p)))
		{
			id[i++] = parser_peek(&p);
			parser_advance(&p);
		}
		id[i] = 0;
		
		if (ft_strcmp(id, "v") == 0) obj_parse_v(&ctx, &p);
		else if (ft_strcmp(id, "vt") == 0) obj_parse_vt(&ctx, &p);
		else if (ft_strcmp(id, "vn") == 0) obj_parse_vn(&ctx, &p);
		else if (ft_strcmp(id, "f") == 0) obj_parse_f(&ctx, &p);
		else if (ft_strcmp(id, "mtllib") == 0) obj_parse_mtllib(&ctx, &p, scene, path);
		else if (ft_strcmp(id, "usemtl") == 0) obj_parse_usemtl(&ctx, &p, scene);
		
		while (parser_peek(&p) && parser_peek(&p) != '\n') parser_advance(&p);
	}
	close(fd);

	ft_print_debug("DEBUG: Parsing finished. Initial vertices count: %zu\n", ctx.v_count);
	for (size_t i = 0; i < ctx.v_count && i < 5; i++)
	{
		ft_print_debug("DEBUG: v[%zu]: ", i);
		print_vec3(&ctx.temp_v[i]);
		ft_print_debug("\n");
	}

	if (ctx.out_v_count == 0) { free(ctx.temp_v); free(ctx.temp_vt); free(ctx.temp_vn); return (false); }

	/* Generate normals if missing */
	if (ctx.vn_count == 0)
	{
		ft_print_debug("DEBUG: Generating normals for %s\n", path);
		ctx.out_vn = ft_calloc(ctx.out_v_count, sizeof(t_vec3));
		if (ctx.out_vn)
		{
			for (size_t i = 0; i < ctx.out_i_count; i += 3)
			{
				int i0 = ctx.out_i[i], i1 = ctx.out_i[i+1], i2 = ctx.out_i[i+2];
				t_vec3 v0 = ctx.out_v[i0], v1 = ctx.out_v[i1], v2 = ctx.out_v[i2];
				t_vec3 fn = vec3_cross(vec3_sub(v1, v0), vec3_sub(v2, v0));
				ctx.out_vn[i0] = vec3_add(ctx.out_vn[i0], fn);
				ctx.out_vn[i1] = vec3_add(ctx.out_vn[i1], fn);
				ctx.out_vn[i2] = vec3_add(ctx.out_vn[i2], fn);
			}
			for (size_t i = 0; i < ctx.out_v_count; i++)
				ctx.out_vn[i] = vec3_norm(ctx.out_vn[i]);
			ctx.vn_count = ctx.out_v_count;
		}
	}

	t_mesh mesh;
	ft_memset(&mesh, 0, sizeof(t_mesh));
	mesh.name = ft_strdup(path);
	mesh.vertices = ctx.out_v;
	mesh.normals = ctx.out_vn;
	mesh.uvs = ctx.out_vt;
	mesh.indices = ctx.out_i;
	mesh.vertex_count = ctx.out_v_count;
	mesh.tri_count = ctx.out_i_count / 3;
	mesh.bbox = ctx.bbox;
	mesh.mat_id = ctx.current_mat_id >= 0 ? ctx.current_mat_id : 0;
	
	if (ctx.out_vn) ft_print_debug("DEBUG: OBJ %s has %zu normals.\n", path, ctx.vn_count);
	else ft_print_debug("DEBUG: OBJ %s has NO normals.\n", path);

	print_obj_ctx(&ctx);
	free(ctx.temp_v); free(ctx.temp_vt); free(ctx.temp_vn);
	
	mesh_build_bvh(&mesh);
	ft_print_debug("DEBUG: OBJ parse complete: %d triangles, %d vertices.\n", mesh.tri_count, mesh.vertex_count);
	print_mesh(&mesh);
	scene_add_mesh(scene, mesh);
	return (true);
}
