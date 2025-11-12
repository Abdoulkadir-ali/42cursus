/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:05:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return (r);
}

t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return (r);
}

t_vec3	vec3_multiply(t_vec3 a, t_vec3 b)
{
	t_vec3	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	r.z = a.z * b.z;
	return (r);
}

t_vec3	vec3_divide(t_vec3 a, t_vec3 b)
{
	t_vec3 r;

	if (b.x)
		r.x = a.x / b.x;
	if (b.y)
		r.y = a.y / b.y;
	if (b.z)
		r.z = a.z / b.z;
	return (r);
}