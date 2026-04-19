/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:20:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:20:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
    std::cout << "=== ClapTrap Tests ===" << std::endl;
    ClapTrap clap("ClapBot");
    clap.attack("dummy");
    clap.takeDamage(5);
    clap.beRepaired(3);
    clap.takeDamage(100);
    clap.attack("dummy");   

    std::cout << "\n=== ScavTrap Tests ===" << std::endl;
    ScavTrap scav("ScavBot");
    scav.attack("dummy");
    scav.takeDamage(50);
    scav.beRepaired(20);
    scav.guardGate();

    std::cout << "\n=== FragTrap Tests ===" << std::endl;
    FragTrap frag("FragBot");
    frag.attack("dummy");
    frag.takeDamage(80);
    frag.beRepaired(10);
    frag.highFivesGuys();

    std::cout << "\n=== Construction/Destruction Order ===" << std::endl;
    {
        ScavTrap s("Chaining");
    }

    std::cout << "\n=== End ===" << std::endl;
    return 0;
}
