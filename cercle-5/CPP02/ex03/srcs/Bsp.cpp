/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 05:17:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 06:02:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"


static bool orient(Point const a, Point const b, Point const c)
{
    Fixed v = (a.getX() - c.getX()) * (b.getY() - c.getY())
            - (b.getX() - c.getX()) * (a.getY() - c.getY());
    return v > Fixed(0);
}

bool bsp(Point const p1, Point const p2, Point const p3, Point const pt)
{
    bool b1 = orient(pt, p1, p2);
    bool b2 = orient(pt, p2, p3);
    bool b3 = orient(pt, p3, p1);
    return ((b1 == b2) && (b2 == b3));
}