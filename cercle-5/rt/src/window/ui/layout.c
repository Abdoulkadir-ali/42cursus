/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layout.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 23:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/24 22:43:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ui.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>

t_panel_layout	g_layout = {
	-1, -1, 0, -1, -1, 0, -1, -1, 0, -1, -1, 0,
	-1, -1, 0, -1, -1, 0, -1, -1, 0, -1, -1, 0,
	0, 0, 0
};

static void	resolve_path(char *out, size_t cap)
{
	const char	*home;

	home = getenv("HOME");
	if (!home || !*home)
		home = "/tmp";
	snprintf(out, cap, "%s/.config/miniRT", home);
	mkdir(out, 0755);
	snprintf(out, cap, "%s/.config/miniRT/layout.cfg", home);
}

void	layout_load(void)
{
	char	path[512];
	FILE	*f;
	int		r;

	resolve_path(path, sizeof(path));
	f = fopen(path, "r");
	if (!f)
		return ;
	r = fscanf(f, "settings %d %d %d\n", &g_layout.settings_x, &g_layout.settings_y, &g_layout.settings_h);
	r += fscanf(f, "inspector %d %d %d\n", &g_layout.inspector_x, &g_layout.inspector_y, &g_layout.inspector_h);
	r += fscanf(f, "scene %d %d %d\n", &g_layout.scene_x, &g_layout.scene_y, &g_layout.scene_h);
	r += fscanf(f, "physics %d %d %d\n", &g_layout.physics_x, &g_layout.physics_y, &g_layout.physics_h);
	r += fscanf(f, "animation %d %d %d\n", &g_layout.animation_x, &g_layout.animation_y, &g_layout.animation_h);
	r += fscanf(f, "xfm %d %d %d\n", &g_layout.xfm_x, &g_layout.xfm_y, &g_layout.xfm_h);
	r += fscanf(f, "obj_phys %d %d %d\n", &g_layout.obj_phys_x, &g_layout.obj_phys_y, &g_layout.obj_phys_h);
	r += fscanf(f, "obj_mat %d %d %d\n", &g_layout.obj_mat_x, &g_layout.obj_mat_y, &g_layout.obj_mat_h);
	r += fscanf(f, "scrolls %d %d\n", &g_layout.scene_scroll, &g_layout.obj_scroll);
	r += fscanf(f, "theme %d\n", &g_layout.theme_preset);
	(void)r;
	fclose(f);
}

void	layout_save(void)
{
	char	path[512];
	FILE	*f;

	resolve_path(path, sizeof(path));
	f = fopen(path, "w");
	if (!f)
		return ;
	fprintf(f, "settings %d %d %d\n", g_layout.settings_x, g_layout.settings_y, g_layout.settings_h);
	fprintf(f, "inspector %d %d %d\n", g_layout.inspector_x, g_layout.inspector_y, g_layout.inspector_h);
	fprintf(f, "scene %d %d %d\n", g_layout.scene_x, g_layout.scene_y, g_layout.scene_h);
	fprintf(f, "physics %d %d %d\n", g_layout.physics_x, g_layout.physics_y, g_layout.physics_h);
	fprintf(f, "animation %d %d %d\n", g_layout.animation_x, g_layout.animation_y, g_layout.animation_h);
	fprintf(f, "xfm %d %d %d\n", g_layout.xfm_x, g_layout.xfm_y, g_layout.xfm_h);
	fprintf(f, "obj_phys %d %d %d\n", g_layout.obj_phys_x, g_layout.obj_phys_y, g_layout.obj_phys_h);
	fprintf(f, "obj_mat %d %d %d\n", g_layout.obj_mat_x, g_layout.obj_mat_y, g_layout.obj_mat_h);
	fprintf(f, "scrolls %d %d\n", g_layout.scene_scroll, g_layout.obj_scroll);
	fprintf(f, "theme %d\n", g_layout.theme_preset);
	fclose(f);
}
