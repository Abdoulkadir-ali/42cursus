#include "scene.h"

int	scene_allocate_object_slot(void **ptr, int *count, int *cap, size_t sz)
{
	if (!DYNARRAY_ENSURE_INT(ptr, count, cap, sz))
		return (-1);
	return ((*count)++);
}
