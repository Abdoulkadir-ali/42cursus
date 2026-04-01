#include "functions/gui/render.h"
#include "functions/helpers/profiler.h"
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

static void render_tile(t_render *render, int id)
{
	t_tile v;

	v.tile.x = (id % render->tiles_count.x) * TILE_SIZE;
	v.tile.y = (id / render->tiles_count.x) * TILE_SIZE;
	v.p_pos.y = v.tile.y;
	v.row_ptr = render->gui->win.addr + (v.p_pos.y * render->gui->win.line_len) + (v.tile.x * (render->gui->win.bpp / 8));
	v.bpp_step = (render->gui->win.bpp / 8) * render->step;
	v.row_step = render->gui->win.line_len * render->step;
	while (v.p_pos.y < v.tile.y + TILE_SIZE && v.p_pos.y < render->gui->win.size.y)
	{
		v.p_pos.x = v.tile.x;
		v.pixel_ptr = v.row_ptr;
		while (v.p_pos.x < v.tile.x + TILE_SIZE && v.p_pos.x < render->gui->win.size.x)
		{
			process_pixel(render, vec2i(v.p_pos.x, v.p_pos.y), v.pixel_ptr);
			v.p_pos.x += render->step;
			v.pixel_ptr += v.bpp_step;
		}
		v.p_pos.y += render->step;
		v.row_ptr += v.row_step;
	}
}

static void *render_tile_worker(void *ptr)
{
	t_worker *arg = (t_worker *)ptr;
	t_render_pool *pool = arg->pool;
	int idx = arg->idx;
	t_render *render;
	int id;

	free(arg);
	while (1)
	{
		sem_wait(&pool->start[idx]);
		if (pool->shutdown)
			break ;
		render = pool->render[idx];
		while (1)
		{
			id = __sync_fetch_and_add(&render->next_tile_id, 1);
			if (id >= render->total_tiles)
				break ;
			render_tile(render, id);
		}
		PROF_FLUSH();
		sem_post(&pool->done[idx]);
	}
	return (NULL);
}

static void init_render_pool(t_render_pool *pool, int n)
{
	int i;
	t_worker *arg;

	pool->n = n;
	pool->shutdown = false;
	i = 0;
	while (i < n)
	{
		sem_init(&pool->start[i], 0, 0);
		sem_init(&pool->done[i], 0, 0);
		pool->render[i] = NULL;
		arg = malloc(sizeof(t_worker));
		arg->pool = pool;
		arg->idx = i;
		pthread_create(&pool->threads[i], NULL, render_tile_worker, arg);
		i++;
	}
	pool->ready = true;
}

void render_tiles(t_render *render)
{
	int num_cores;
	int i;
	t_render_pool *pool;

	num_cores = render->gui->render.num_cores;
	pool = &render->gui->render.pool;
	if (num_cores < 1)
		return ;
	if (!pool->ready)
		init_render_pool(pool, num_cores);
	i = 0;
	while (i < num_cores)
	{
		pool->render[i] = render;
		sem_post(&pool->start[i]);
		i++;
	}
	i = 0;
	while (i < num_cores)
	{
		sem_wait(&pool->done[i]);
		i++;
	}
}
