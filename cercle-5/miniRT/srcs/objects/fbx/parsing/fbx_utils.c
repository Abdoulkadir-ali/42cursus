#include "objects.h"

void	fbx_build_flat(t_mesh *m, int *raw, int raw_c, \
	t_vec3 *n, int nc, t_vec2 *u, int uc, int vc)
{
	ft_print_debug("DEBUG: Starting fbx_build_flat (raw_c=%d, vc=%d)\n", raw_c, vc);
	t_vec2	*nu;
	t_vec3	*nv;
	t_vec3	*nn;
	int		si;
	int		idx;
	int		vn;
	int		i;
	int		ps;
	int		vg;
	int		vp;
	int		*ni;
	int		*v;
	int		tc;
	int		use_v_n;
	int		use_v_u;

	ps = 0;
	tc = 0;
	while (ps < raw_c)
	{
		vn = 0;
		while (ps < raw_c)
		{
			idx = raw[ps++];
			vn++;
			if (idx < 0)
				break ;
		}
		if (vn >= 3)
			tc += (vn - 2);
	}
	m->tri_count = tc;
	if (tc <= 0) return ;
	nv = ft_calloc(tc * 3, sizeof(t_vec3));
	nn = n ? ft_calloc(tc * 3, sizeof(t_vec3)) : NULL;
	nu = u ? ft_calloc(tc * 3, sizeof(t_vec2)) : NULL;
	ni = ft_calloc(tc * 3, sizeof(int));
	if (!nv || !ni || (n && !nn) || (u && !nu))
	{
		if (nv) free(nv);
		if (ni) free(ni);
		if (nn) free(nn);
		if (nu) free(nu);
		return ;
	}
	v = malloc(sizeof(int) * raw_c);
	if (!v)
	{
		if (nv) free(nv);
		if (ni) free(ni);
		if (nn) free(nn);
		if (nu) free(nu);
		return ;
	}
	use_v_n = (n && nc > 0 && nc < tc * 3);
	use_v_u = (u && uc > 0 && uc < tc * 3);
	ps = 0; vp = 0; vg = 0;
	while (ps < raw_c)
	{
		vn = 0;
		si = vg;
		while (ps < raw_c)
		{
			idx = raw[ps++];
			v[vn++] = (idx < 0) ? (idx ^ -1) : idx;
			vg++;
			if (idx < 0)
				break ;
		}
		for (i = 1; i < vn - 1; i++)
		{
			if (v[0] < vc && v[i] < vc && v[i + 1] < vc && vp < tc * 3 - 2)
			{
				nv[vp] = m->vertices[v[0]];
				if (nn) nn[vp] = use_v_n ? n[v[0] % nc] : n[(si + 0) % nc];
				if (nu) nu[vp] = use_v_u ? u[v[0] % uc] : u[(si + 0) % uc];
				ni[vp] = vp; vp++;
				nv[vp] = m->vertices[v[i]];
				if (nn) nn[vp] = use_v_n ? n[v[i] % nc] : n[(si + i) % nc];
				if (nu) nu[vp] = use_v_u ? u[v[i] % uc] : u[(si + i) % uc];
				ni[vp] = vp; vp++;
				nv[vp] = m->vertices[v[i + 1]];
				if (nn) nn[vp] = use_v_n ? n[v[i + 1] % nc] : n[(si + i + 1) % nc];
				if (nu) nu[vp] = use_v_u ? u[v[i + 1] % uc] : u[(si + i + 1) % uc];
				ni[vp] = vp; vp++;
			}
		}
	}
	free(v);
	free(m->vertices);
	m->vertices = nv;
	m->normals = nn;
	m->uvs = nu;
	m->indices = ni;
	ft_print_debug("DEBUG: fbx_build_flat final count: %d vertices (%d tris)\n", vp, vp / 3);
	m->vertex_count = vp;
	m->tri_count = vp / 3;
}
