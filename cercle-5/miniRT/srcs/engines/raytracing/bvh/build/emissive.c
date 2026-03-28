#include "raytracing.h"

static bool is_emissive(const t_scene *sc, int mat_id)
{
	t_vec3 e;
	if (mat_id < 0 || (size_t)mat_id >= sc->mat_count)
		return (false);
	e = sc->materials[mat_id].emission;
	return ((e.x * e.x + e.y * e.y + e.z * e.z) > 1.0);
}

static int add_emissives_impl(const t_scene *sc, t_emissive_ref *ca)
{
	size_t i;
	int n;
	n = 0;
	i = 0;
	while (i < sc->primitives.count)
	{
		if (is_emissive(sc, sc->primitives.mat_ids[i]))
		{
			ca[n].type = (t_type)sc->primitives.types[i];
			ca[n].index = (int)i;
			n++;
		}
		i++;
	}
	i = 0;
	while (i < sc->tri_soa.count)
	{
		if (is_emissive(sc, sc->tri_soa.mat_ids[i]))
		{
			ca[n].type = TYPE_TRI;
			ca[n].index = (int)i;
			n++;
		}
		i++;
	}
	return (n);
}

void build_emissive_cache(t_scene *sc)
{
	t_emissive_ref *cache;
	size_t cap;

	free(sc->emissive_cache);
	sc->emissive_cache = NULL;
	sc->emissive_count = 0;
	cap = sc->primitives.count + sc->tri_soa.count;
	if (cap == 0)
		return;
	cache = malloc(sizeof(t_emissive_ref) * cap);
	if (!cache)
		return;
	sc->emissive_count = add_emissives_impl(sc, cache);
	sc->emissive_cache = cache;
}
