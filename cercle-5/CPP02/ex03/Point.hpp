/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:14:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 03:22:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Fixed.hpp"

class Point {
private:
    const Fixed x;
    const Fixed y;
public:
    Point();
    Point(const Point& p);
    Point& operator=(const Point& p);
    Point(const float x, const float y);
    ~Point();
    Fixed getX() const;
    Fixed getY() const;
};

std::ostream& operator<<(std::ostream& out, const Point& p);
// Optionally, declare bsp if needed:
// bool bsp(Point const a, Point const b, Point const c, Point const p);