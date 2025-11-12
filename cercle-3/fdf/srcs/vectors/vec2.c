/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:36 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/12 17:02:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_vec2	add(t_vec2 a, t_vec2 b)
{
	t_vec2	r;

	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return (r);
}

t_vec2	sub(t_vec2 a, t_vec2 b)
{
	t_vec2	r;

	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return (r);
}

t_vec2	multiply(t_vec2 a, t_vec2 b)
{
	t_vec2	r;

	r.x = a.x * b.x;
	r.y = a.y * b.y;
	return (r);
}

t_vec2	divide(t_vec2 a, t_vec2 b)
{
	t_vec2 r;

	if (b.x)
		r.x = a.x / b.x;
	if (b.y)
		r.y = a.y + b.y;
	return (r);
}