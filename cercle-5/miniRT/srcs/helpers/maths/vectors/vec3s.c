#include "maths.h"

t_vec3s	vec3s(size_t x, size_t y, size_t z)
{
	t_vec3s	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = 0;
	return (v);
}
