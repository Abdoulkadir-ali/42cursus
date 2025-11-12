/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:05:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec3d	vec3d_add(t_vec3d a, t_vec3d b)
{
	t_vec3d	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return (r);
}

t_vec3d	vec3d_sub(t_vec3d a, t_vec3d b)
{
	t_vec3d	r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return (r);
}

t_vec3d	vec3d_multiply(t_vec3d a, t_vec3d b)
{
	t_vec3d	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	return (r);
}

t_vec3d	vec3d_divide(t_vec3d a, t_vec3d b)
{
	t_vec3d r;

	if (b.x)
		r.x = a.x / b.x;
	if (b.y)
		r.y = a.y / b.y;
	if (b.z)
		r.z = a.z / b.z;
	return (r);
}