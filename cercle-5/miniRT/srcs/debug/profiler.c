/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/29 09:39:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef PROFILE_MESH

#include "debug.h"

static volatile _Atomic long	g_mesh_calls = 0;
static volatile _Atomic long	g_mesh_aabb_tests = 0;
static volatile _Atomic long	g_mesh_tri_tests = 0;
static volatile _Atomic long	g_mesh_occ_calls = 0;
static int						g_prof_frame = 0;
static struct timespec			g_prof_start;

static __thread long	tl_g_mesh_calls = 0;
static __thread long	tl_g_mesh_aabb_tests = 0;
static __thread long	tl_g_mesh_tri_tests = 0;
static __thread long	tl_g_mesh_occ_calls = 0;

static double	g_frame_times[1024];
static int		g_frame_count = 0;

void	prof_print_frame(void)
{
	struct timespec	end;
	double			ms;
	double			avg;
	int				i;
	int				max_frames;

	clock_gettime(CLOCK_MONOTONIC, &end);
	ms = (end.tv_sec - g_prof_start.tv_sec) * 1000.0
		+ (end.tv_nsec - g_prof_start.tv_nsec) / 1e6;
	/* printf("PROF[%d]: %.1fms (%.1f FPS) mesh=%ld aabb=%ld tri=%ld occ=%ld\n",
		g_prof_frame, ms, 1000.0 / ms,
		g_mesh_calls, g_mesh_aabb_tests, g_mesh_tri_tests, g_mesh_occ_calls); */
	fflush(stdout);
	if (g_frame_count < 1024)
		g_frame_times[g_frame_count++] = ms;
	g_prof_frame++;
	max_frames = 20;
	if (getenv("BENCH_FRAMES"))
		max_frames = atoi(getenv("BENCH_FRAMES"));
	if (g_prof_frame == max_frames)
	{
		avg = 0;
		i = 2;
		while (i < g_frame_count)
		{
			avg += g_frame_times[i];
			i++;
		}
		if (g_frame_count > 2)
			avg /= (g_frame_count - 2);
		printf("\n=== BENCHMARK (%d frames, skipped first 2) ===\n", max_frames);
		printf("Avg frame: %.1f ms (%.1f FPS)\n", avg, 1000.0 / avg);
		fflush(stdout);
	}
}

void	prof_inc(t_prof_id id)
{
	switch (id)
	{
	case PROF_MESH_CALLS:
		tl_g_mesh_calls++;
		break;
	case PROF_MESH_AABB_TESTS:
		tl_g_mesh_aabb_tests++;
		break;
	case PROF_MESH_TRI_TESTS:
		tl_g_mesh_tri_tests++;
		break;
	case PROF_MESH_OCC_CALLS:
		tl_g_mesh_occ_calls++;
		break;
	default:
		break;
	}
}

void	prof_flush(void)
{
	atomic_fetch_add_explicit(&g_mesh_calls, tl_g_mesh_calls,
		memory_order_relaxed);
	atomic_fetch_add_explicit(&g_mesh_aabb_tests, tl_g_mesh_aabb_tests,
		memory_order_relaxed);
	atomic_fetch_add_explicit(&g_mesh_tri_tests, tl_g_mesh_tri_tests,
		memory_order_relaxed);
	atomic_fetch_add_explicit(&g_mesh_occ_calls, tl_g_mesh_occ_calls,
		memory_order_relaxed);
	tl_g_mesh_calls = 0; tl_g_mesh_aabb_tests = 0;
	tl_g_mesh_tri_tests = 0; tl_g_mesh_occ_calls = 0;
}

void	prof_reset(void)
{
	g_mesh_calls = 0; g_mesh_aabb_tests = 0;
	g_mesh_tri_tests = 0; g_mesh_occ_calls = 0;
	clock_gettime(CLOCK_MONOTONIC, &g_prof_start);
}

#endif
