/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/23 15:03:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROFILER_H
# define PROFILER_H

# include "types.h"
# include <time.h>
# include <sys/stat.h>


# ifdef PROFILE_MESH

#  if defined(PROFILE_BUILD)
#   include <valgrind/callgrind.h>
#  endif
/* Allow update.c (PROFILE_BUILD) to read the frame counter */
#  define g_prof_frame g_profiler.frame

typedef struct s_profiler
{
	volatile long	mesh_calls;
	volatile long	mesh_aabb_tests;
	volatile long	mesh_tri_tests;
	volatile long	mesh_occ_calls;
	int				frame;
	int				frame_count;
	double			frame_times[1024];
	struct timespec	start;
}	t_profiler;

extern t_profiler	g_profiler;

#  define PROF_INC(f) (__sync_fetch_and_add(&g_profiler.f, 1))
#  define PROF_FLUSH()
#  define PROF_RESET() do { \
	g_profiler.mesh_calls = 0; g_profiler.mesh_aabb_tests = 0; \
	g_profiler.mesh_tri_tests = 0; g_profiler.mesh_occ_calls = 0; \
	clock_gettime(CLOCK_MONOTONIC, &g_profiler.start); } while (0)
#  define PROF_PRINT() prof_print_frame()

void	prof_print_frame(void);

# else

#  define PROF_INC(x)
#  define PROF_FLUSH()
#  define PROF_RESET()
#  define PROF_PRINT()

# endif
#endif
