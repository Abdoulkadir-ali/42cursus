/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: automated <auto@local>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 13:25:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/26 18:20:00 by automated        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "physics.h"

static t_vec3	project_on_edge(t_vec3 p, t_vec3 a, t_vec3 b)
{
    t_vec3	ab;
    t_vec3	ap;
    double	t;

    ab = vec3_sub(b, a);
    ap = vec3_sub(p, a);
    t = fmin(1.0, fmax(0.0, vec3_dot(ap, ab) / vec3_dot(ab, ab)));
    return (vec3_add(a, vec3_scale(ab, t)));
}

static t_vec3	project_on_edges(t_vec3 p, t_vec3 v[3])
{
    t_vec3	p0;
    t_vec3	p1;
    t_vec3	p2;
    double	d[3];

    p0 = project_on_edge(p, v[0], v[1]);
    p1 = project_on_edge(p, v[1], v[2]);
    p2 = project_on_edge(p, v[2], v[0]);
    d[0] = vec3_mag_sq(vec3_sub(p, p0));
    d[1] = vec3_mag_sq(vec3_sub(p, p1));
    d[2] = vec3_mag_sq(vec3_sub(p, p2));
    if (d[0] < d[1] && d[0] < d[2])
        return (p0);
    if (d[1] < d[2])
        return (p1);
    return (p2);
}

t_vec3	closest_point_on_triangle(t_vec3 p, t_vec3 v0, t_vec3 v1, t_vec3 v2)
{
    t_vec3	e[2];
    t_vec2	st;
    double	abc[3];
    double	det;

    e[0] = vec3_sub(v1, v0);
    e[1] = vec3_sub(v2, v0);
    abc[0] = vec3_dot(e[0], e[0]);
    abc[1] = vec3_dot(e[0], e[1]);
    abc[2] = vec3_dot(e[1], e[1]);
    det = abc[0] * abc[2] - abc[1] * abc[1];
    st.x = abc[1] * vec3_dot(e[1], vec3_sub(p, v0)) - abc[2] * vec3_dot(e[0],
            vec3_sub(p, v0));
    st.y = abc[1] * vec3_dot(e[0], vec3_sub(p, v0)) - abc[0] * vec3_dot(e[1],
            vec3_sub(p, v0));
    if (st.x + st.y < det && st.x >= 0.0 && st.y >= 0.0)
    {
        st.x /= det;
        st.y /= det;
        return (vec3_add(v0, vec3_add(vec3_scale(e[0], st.x), vec3_scale(e[1],
                        st.y))));
    }
    return (project_on_edges(p, (t_vec3[]){v0, v1, v2}));
}
