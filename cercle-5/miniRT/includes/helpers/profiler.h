/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   profiler.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 12:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROFILER_H
# define PROFILER_H

# include "libft.h"
# include <time.h>

# ifdef PROFILE_MESH

typedef enum e_prof_id
{
	PROF_MESH_CALLS,
	PROF_MESH_AABB_TESTS,
	PROF_MESH_TRI_TESTS,
	PROF_MESH_OCC_CALLS,
}	t_prof_id;

/* Mapping from legacy global identifiers to profiler IDs */
#  define PROF_ID_g_mesh_calls      PROF_MESH_CALLS
#  define PROF_ID_g_mesh_aabb_tests PROF_MESH_AABB_TESTS
#  define PROF_ID_g_mesh_tri_tests  PROF_MESH_TRI_TESTS
#  define PROF_ID_g_mesh_occ_calls  PROF_MESH_OCC_CALLS

/* Runtime API — srcs/helpers/debug/ */
void	prof_inc(t_prof_id id);
void	prof_flush(void);
void	prof_reset(void);
void	prof_print_frame(void);

#  define PROF_INC(x)  prof_inc(PROF_ID_##x)
#  define PROF_FLUSH() prof_flush()
#  define PROF_RESET() prof_reset()
#  define PROF_PRINT() prof_print_frame()

# else /* PROFILE_MESH not defined — all macros are no-ops */

#  define PROF_INC(x)
#  define PROF_FLUSH()
#  define PROF_RESET()
#  define PROF_PRINT()

# endif /* PROFILE_MESH */

#endif /* PROFILER_H */
