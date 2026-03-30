bool	scene_add_tri(t_scene *scene, t_tri_shape tri)
{
	int	mat_id;

	mat_id = scene_add_material(scene, tri.temp_color);
	if (mat_id < 0)
		return (false);
	tri.mat_id = mat_id;
	if (!DYNARRAY_ENSURE_INT(&scene->tris, &scene->tri_count,
			&scene->tri_cap, sizeof(t_tri_shape)))
		return (false);
	scene->tris[scene->tri_count++] = tri;
	return (true);
}
