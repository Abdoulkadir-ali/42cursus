/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/02/15 06:32:25 by abdoali          ###   ########.fr       */
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

#  define PROF_INC(x) __sync_fetch_and_add(&(x), 1)
#  define PROF_RESET() do { g_mesh_calls = 0; g_mesh_aabb_tests = 0; \
	g_mesh_tri_tests = 0; g_mesh_occ_calls = 0; \
	clock_gettime(CLOCK_MONOTONIC, &g_prof_start); } while (0)
#  define PROF_PRINT() prof_print_frame()

void	prof_print_frame(void);

# else

#  define PROF_INC(x)
#  define PROF_RESET()
#  define PROF_PRINT()

# endif
#endif
