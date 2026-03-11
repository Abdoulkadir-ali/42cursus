/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:53:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:57:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Human.hpp"

Human::Human(std::string name, int hp) : _name(name), _hp(hp), _weapon(NULL)
{
}

Human::~Human(void)
{
}

void Human::takeDamage(int amount)
{
    if (this->_hp > 0)
    {
        this->_hp -= amount;
        if (this->_hp < 0) this->_hp = 0;
        std::cout << this->_name << " has now " << this->_hp << " HP left." << std::endl;
    }
    else
    {
        std::cout << this->_name << " is already dead, stop hitting them!" << std::endl;
    }
}

const std::string &Human::getName(void) const
{
    return (this->_name);
}

void Human::attack(Human &target)
{
    if (this->_hp <= 0)
    {
        std::cout << this->_name << " is dead and cannot attack." << std::endl;
        return;
    }

    int damage = 0;
    std::string weaponName = "bare fists";
    if (this->_weapon)
    {
        damage = this->_weapon->getDamage();
        weaponName = this->_weapon->getType();
    }
    else
    {
        damage = 5 + (rand() % 6); // 5-10 damage for fists
    }
    
    std::cout << this->_name << " attacks " << target.getName() << " using " << weaponName 
              << ", inflicting " << damage << " points of damage!" << std::endl;
    target.takeDamage(damage);
}

void Human::attack(void)
{
    if (this->_hp <= 0)
    {
        std::cout << this->_name << " is dead and cannot attack." << std::endl;
        return;
    }

    if (this->_weapon)
        std::cout << this->_name << " attacks with their " << this->_weapon->getType() << std::endl;
    else
        std::cout << this->_name << " attacks with their bare fists" << std::endl;
}
