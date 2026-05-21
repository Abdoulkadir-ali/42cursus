/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 18:47:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/02 16:41:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"

int	parse_lines(char *buf, t_app *app)
{
	char	*line;
	char	*next;
	char	*toks[32];
	int		n;
	int		ln;

	line = buf;
	ln = 0;
	while (line && *line)
	{
		ln++;
		next = strchr(line, '\n');
		if (next)
			*next++ = '\0';
		n = tokenize(line, toks, 32);
		if (n > 0 && !dispatch(toks, n, app))
		{
			fprintf(stderr, "Error\nparse failed at line %d: %s\n", ln, toks[0]);
			return (0);
		}
		line = next;
	}
	return (1);
}

static int	parse_mesh(const char *path, t_app *app, size_t len)
{
	t_mesh_conf	conf;
	int			ok;

	setup_default_scene(app);
	app->set.rt.emitters_as_lights = 0;
	ft_bzero(&conf, sizeof(t_mesh_conf));
	conf.origin = v3(0, 0, 0);
	conf.scale = 1.0f;
	conf.color = v3(1, 1, 1);
	if (!strcmp(path + len - 4, ".glb"))
		ok = (mesh_load_glb(&app->scene, path, &conf) == 0);
	else
	{
		conf.scale = 0.1f;
		conf.zscale = 0.1f;
		ok = (mesh_load_fdf(&app->scene, path, &conf) == 0);
	}
	if (ok)
	{
		autoorient_mesh(app);
		autoframe_camera(app);
		cache_imported_file(path);
	}
	return (ok);
}

static int	parse_rt(const char *path, t_app *app)
{
	char	*buf;
	int		ok;

	buf = read_file_all(path);
	if (!buf)
		return (fprintf(stderr, "Error\ncannot read %s\n", path), 0);
	ok = parse_lines(buf, app);
	if (ok)
		cache_imported_file(path);
	free(buf);
	if (ok && (!app->scene.amb.set || !app->scene.cam_set))
	{
		fprintf(stderr, "Error\nmissing A or C\n");
		return (0);
	}
	return (ok);
}

int	parse_file(const char *path, t_app *app)
{
	size_t	len;

	if (!path)
		return (0);
	if (is_file_imported(path))
	{
		fprintf(stderr, "Warning: file '%s' already imported\n", path);
		return (1);
	}
	len = strlen(path);
	if (len > 4 && (!strcmp(path + len - 4, ".glb")
			|| !strcmp(path + len - 4, ".fdf")))
		return (parse_mesh(path, app, len));
	if (len < 3 || strcmp(path + len - 3, ".rt") != 0)
	{
		fprintf(stderr, "Error\nfile must end with .rt, .glb or .fdf\n");
		return (0);
	}
	if (!parse_rt(path, app))
		return (0);
	bvh_rebuild(app);
	phys_ensure_all_bodies(app);
	return (1);
}