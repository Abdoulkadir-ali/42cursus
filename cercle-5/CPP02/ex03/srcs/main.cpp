/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 05:57:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bsp.hpp"

int main()
{
    Point a(0, 0);
    Point b(1, 1);
    Point c(2, 2);

    std::cout << "Point a: " << a << std::endl;
    std::cout << "Point b: " << b << std::endl;
    std::cout << "Point c: " << c << std::endl;

    Point p(1, 0.5);
    bool inside = bsp(a, b, c, p);
    std::cout << "Point p is " << (inside ? "inside" : "outside") << " the triangle." << std::endl;

    return 0;
}