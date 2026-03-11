/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:33:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 17:46:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
    : type("ScavTrap"), hp(10), energy(10), damage(20)
{
    ClapTrap(this->type, this->hp, this->energy, this->damage);
    std::cout << this->type << " Constructor called" << std::endl;
}

ScavTrap::ScavTrap(const unsigned int hp, const unsigned int energy, const unsigned int damage)
    : ClapTrap("ScavTrap", hp, energy, damage)
{
    std::cout << this->type << " Parametrized constructor called" << std::endl;
}

ScavTrap::~ScavTrap(void)
{
	std::cout << this->type << " Desctructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (this->energy)
    {
        std::cout << this->type << " attacks " << target << ", causing " << this->damage << " points of damage!" << std::endl;
        this->energy--;
    }
    else
        std::cout << this->type << " " << this->name << " does not have enough energy to launch attack" << std::endl;
}

void ScavTrap::guardGate(void)
{
    std::cout << this->type << "Enters in keeper mode" << std::endl;
}