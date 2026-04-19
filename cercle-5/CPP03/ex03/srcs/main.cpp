/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:23:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

int main()
{
    std::cout << "=== DiamondTrap construction/destruction chaining ===" << std::endl;
    {
        DiamondTrap d("Gem");

        std::cout << "\n--- whoAmI ---" << std::endl;
        d.whoAmI();

        std::cout << "\n--- attack (ScavTrap's) ---" << std::endl;
        d.attack("Target");

        std::cout << "\n--- takeDamage ---" << std::endl;
        d.takeDamage(50);

        std::cout << "\n--- beRepaired ---" << std::endl;
        d.beRepaired(30);

        std::cout << "\n--- guardGate (ScavTrap) ---" << std::endl;
        d.guardGate();

        std::cout << "\n--- highFivesGuys (FragTrap) ---" << std::endl;
        d.highFivesGuys();

        std::cout << "\n--- End of scope: destruction order ---" << std::endl;
    }
    return 0;
}
