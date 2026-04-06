#include "maths.h"

t_vec2s	vec2s(size_t x, size_t y)
{
	t_vec2s	v;

	v.x = x;
	v.y = y;
	return (v);
}

t_vec2s	vec2s_add(t_vec2s a, t_vec2s b)
{
	return ((t_vec2s){a.x + b.x, a.y + b.y});
}

t_vec2s	vec2s_sub(t_vec2s a, t_vec2s b)
{
	return ((t_vec2s){a.x - b.x, a.y - b.y});
}
