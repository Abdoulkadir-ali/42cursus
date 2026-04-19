/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:56:04 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    std::cout << "=== ClapTrap Tests ===" << std::endl;
    ClapTrap a("Alpha");

    a.attack("Target");
    a.takeDamage(5);
    a.beRepaired(3);
    a.takeDamage(100);
    a.attack("Target");
    a.beRepaired(5);

    std::cout << "\n=== Copy Constructor Test ===" << std::endl;
    ClapTrap b(a);
    b.attack("Target");

    std::cout << "\n=== Energy Drain Test ===" << std::endl;
    {
        ClapTrap c("Drainer");
        for (int i = 0; i < 11; i++)
            c.attack("Target");
    }

    std::cout << "\n=== End ===" << std::endl;
    return 0;
}