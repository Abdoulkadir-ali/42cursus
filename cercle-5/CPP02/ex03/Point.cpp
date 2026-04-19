/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 03:22:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "Point.hpp"
 #include <iostream>

Point::Point()
    : x(0), y(0)
{
    std::cout << "Constructor called" << std::endl;
}

Point::Point(const Point& p): x(p.x), y(p.y)
{   
}

Point& Point::operator=(const Point& p)
{
    (void)p;
    return *this;
}

Point::Point(const float x, const float y) : x(x), y(y)
{
}

Point::~Point()
{
    std::cout << "Destructor called" << std::endl;
}

Fixed Point::getX() const
{
    return x;
}

Fixed Point::getY() const
{
    return y;
}

std::ostream& operator<<(std::ostream& out, const Point& p)
{
    out << "(" << p.getX() << ", " << p.getY() << ")";
    return out;
}

