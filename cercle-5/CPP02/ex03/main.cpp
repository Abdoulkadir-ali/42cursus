/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 03:22:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bsp.hpp"

int main()
{
    // Triangle: (0,0), (4,0), (0,4)
    Point a(0.0f, 0.0f);
    Point b(4.0f, 0.0f);
    Point c(0.0f, 4.0f);

    Point inside(1.0f, 1.0f);
    Point onEdge(2.0f, 0.0f);
    Point onVertex(0.0f, 0.0f);
    Point outside(5.0f, 5.0f);

    std::cout << "inside  (1,1):   " << (bsp(a, b, c, inside)   ? "true" : "false") << std::endl;
    std::cout << "on edge (2,0):   " << (bsp(a, b, c, onEdge)   ? "true" : "false") << std::endl;
    std::cout << "on vertex (0,0): " << (bsp(a, b, c, onVertex) ? "true" : "false") << std::endl;
    std::cout << "outside (5,5):   " << (bsp(a, b, c, outside)  ? "true" : "false") << std::endl;

    return 0;
}