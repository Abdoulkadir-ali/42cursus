/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 00:43:00 by abdoali          ###   ########.fr       */
/*   Updated: 2025/12/21 00:43:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Template for vector utility operations.
**
** Required Macros:
** - T_VEC: The vector structure type (e.g. t_vec3)
** - T_SCALAR: The scalar type (e.g. int, double, unsigned int)
** - PREFIX: The function prefix (e.g. vec3)
** - COMPONENT_COUNT: 2 or 3
*/

#ifndef CONCAT
# define CONCAT(a, b) a ## _ ## b
#endif

#ifndef FN_NAME
# define FN_NAME(prefix, name) CONCAT(prefix, name)
#endif

/*
** Note: len returns T_SCALAR or double? Usually length is double or int depending on usage.
** Original code: vec2_len -> int, vec3_len -> double?
** Let's check original. vec3_len returns double usually. vec2_len returned int in header.
** This inconsistency is tricky for templates.
** Solution: Use T_RET macro for return type of len.
*/
#ifndef T_RET
# define T_RET T_SCALAR
#endif

T_RET	FN_NAME(PREFIX, len)(T_VEC v)
{
#if COMPONENT_COUNT == 3
# ifdef IS_FLOAT
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
# else
	return ((T_RET)sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
# endif
#else
# ifdef IS_FLOAT
	return (sqrt(v.x * v.x + v.y * v.y));
# else
	return ((T_RET)sqrt(v.x * v.x + v.y * v.y));
# endif
#endif
}

#ifndef IS_FLOAT
// Only define min/max for integer types if original did so?
// geometry.h had vec2_min / vec2_max returning int.
// No vec3_min/max in header?
T_RET	FN_NAME(PREFIX, min)(T_VEC v)
{
	T_SCALAR	m;

	m = v.x;
	if (v.y < m)
		m = v.y;
#if COMPONENT_COUNT == 3
	if (v.z < m)
		m = v.z;
#endif
	return (m);
}

T_RET	FN_NAME(PREFIX, max)(T_VEC v)
{
	T_SCALAR	m;

	m = v.x;
	if (v.y > m)
		m = v.y;
#if COMPONENT_COUNT == 3
	if (v.z > m)
		m = v.z;
#endif
	return (m);
}
#endif
