/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:05:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec2d	add(t_vec2d a, t_vec2d b)
{
	t_vec2d	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return (r);
}

t_vec2d	sub(t_vec2d a, t_vec2d b)
{
	t_vec2d	r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return (r);
}

t_vec2d	multiply(t_vec2d a, t_vec2d b)
{
	t_vec2d	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	return (r);
}

t_vec2d	divide(t_vec2d a, t_vec2d b)
{
	t_vec2d r;

	if (b.x)
		r.x = a.x / b.x;
	if (b.y)
		r.y = a.y + b.y;
	return (r);
}