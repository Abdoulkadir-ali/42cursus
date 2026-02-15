/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 17:40:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROFILER_H
# define PROFILER_H

# include <time.h>

# ifdef PROFILE_MESH

extern volatile long	g_mesh_calls;
extern volatile long	g_mesh_aabb_tests;
extern volatile long	g_mesh_tri_tests;
extern volatile long	g_mesh_occ_calls;
extern int				g_prof_frame;
extern struct timespec	g_prof_start;

extern __thread long	tl_g_mesh_calls;
extern __thread long	tl_g_mesh_aabb_tests;
extern __thread long	tl_g_mesh_tri_tests;
extern __thread long	tl_g_mesh_occ_calls;

#  define PROF_INC(x) (tl_##x++)
#  define PROF_FLUSH() do { \
	__sync_fetch_and_add(&g_mesh_calls, tl_g_mesh_calls); \
	__sync_fetch_and_add(&g_mesh_aabb_tests, tl_g_mesh_aabb_tests); \
	__sync_fetch_and_add(&g_mesh_tri_tests, tl_g_mesh_tri_tests); \
	__sync_fetch_and_add(&g_mesh_occ_calls, tl_g_mesh_occ_calls); \
	tl_g_mesh_calls = 0; tl_g_mesh_aabb_tests = 0; \
	tl_g_mesh_tri_tests = 0; tl_g_mesh_occ_calls = 0; } while (0)
#  define PROF_RESET() do { g_mesh_calls = 0; g_mesh_aabb_tests = 0; \
	g_mesh_tri_tests = 0; g_mesh_occ_calls = 0; \
	clock_gettime(CLOCK_MONOTONIC, &g_prof_start); } while (0)
#  define PROF_PRINT() prof_print_frame()

void	prof_print_frame(void);

# else

#  define PROF_INC(x)
#  define PROF_FLUSH()
#  define PROF_RESET()
#  define PROF_PRINT()

# endif
#endif
