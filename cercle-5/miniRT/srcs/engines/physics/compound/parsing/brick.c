#include "physics.h"
#include "parser.h"
#include "unpacker.h"

t_sub_shape create_primitive_subshape(t_type type, int index, t_vec3 offset, t_scene *sc)
{
	t_sub_shape b;
	t_aabb a;

	b.type = (t_phys_type)type;
	b.offset = offset;
	b.data = (void *)(size_t)index;
	(void)type;
	a = get_primitive_aabb_soa(&sc->primitives, index);
	b.local_aabb = a;
	return (b);
}

void add_brick_to_body(t_physics_body *body, t_sub_shape brick)
{
	if (body->sub_count >= MAX_SUB_SHAPES)
		return;
	body->sub_shapes[body->sub_count++] = brick;
}
