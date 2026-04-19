/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 05:17:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 03:22:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"


static Fixed crossProduct(Point const &o, Point const &a, Point const &b)
{
    return (a.getX() - o.getX()) * (b.getY() - o.getY())
         - (a.getY() - o.getY()) * (b.getX() - o.getX());
}

bool bsp(Point const a, Point const b, Point const c, Point const point)
{
    Fixed d1 = crossProduct(point, a, b);
    Fixed d2 = crossProduct(point, b, c);
    Fixed d3 = crossProduct(point, c, a);

    Fixed zero(0);
    if (d1 == zero || d2 == zero || d3 == zero)
        return false;

    bool has_neg = (d1 < zero) || (d2 < zero) || (d3 < zero);
    bool has_pos = (d1 > zero) || (d2 > zero) || (d3 > zero);

    return !(has_neg && has_pos);
}