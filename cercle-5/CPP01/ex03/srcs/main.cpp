/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:15:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:58:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HumanA.hpp"
#include "HumanB.hpp"

int main()
{
    std::srand(std::time(NULL));
	{
		Weapon club = Weapon("crude spiked club");
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	{
		Weapon club = Weapon("crude spiked club");
		HumanB jim("Jim");
		jim.setWeapon(club);
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
    {
        // New test for Human attack logic
        Weapon sword("Sword", 50, 70);
        HumanB warrior("Warrior");
        
        warrior.attack(); // Bare fists
        
        warrior.setWeapon(sword);
        warrior.attack(); // Sword
        
        HumanB victim("Victim");
        warrior.attack(victim); // Warrior attacks Victim
        warrior.attack(victim); // Warrior attacks Victim
        warrior.attack(victim); // Warrior attacks Victim (likely dead)

        victim.attack(warrior); // Victim attacks Victim (likely dead)
        warrior.attack(warrior); //Sepuku
        warrior.attack(warrior); //Sepuku
        warrior.attack(warrior); //Sepuku
    }
	return 0;
}
