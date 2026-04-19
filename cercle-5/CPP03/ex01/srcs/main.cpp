/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:55 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:56:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main()
{
    std::cout << "=== ScavTrap construction/destruction chaining ===" << std::endl;
    {
        ScavTrap s("ScavBot");
        s.attack("Target");
        s.takeDamage(50);
        s.beRepaired(20);
        s.guardGate();
    }

    std::cout << "\n=== ClapTrap Tests ===" << std::endl;
    {
        ClapTrap c("ClapBot");
        c.attack("Target");
        c.takeDamage(5);
        c.beRepaired(3);
        c.takeDamage(100);
        c.attack("Target"); // can't: no hp
    }

    std::cout << "\n=== End ===" << std::endl;
    return 0;
}