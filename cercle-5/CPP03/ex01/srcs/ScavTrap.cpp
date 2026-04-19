/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:33:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap()
    : ClapTrap()
{
    this->hp     = 100;
    this->energy = 50;
    this->damage = 20;
    std::cout << "ScavTrap default constructor called" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name)
    : ClapTrap(name)
{
    this->hp     = 100;
    this->energy = 50;
    this->damage = 20;
    std::cout << "ScavTrap " << this->name << " constructor called" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& c)
    : ClapTrap(c)
{
    std::cout << "ScavTrap " << this->name << " copy constructor called" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& c)
{
    if (this != &c)
        ClapTrap::operator=(c);
    return *this;
}

ScavTrap::~ScavTrap()
{
    std::cout << "ScavTrap " << this->name << " destructor called" << std::endl;
}

void ScavTrap::attack(const std::string& target)
{
    if (!this->hp)
    {
        std::cout << "ScavTrap " << this->name
                  << " can't attack, has no hit points!" << std::endl;
        return;
    }
    if (!this->energy)
    {
        std::cout << "ScavTrap " << this->name
                  << " can't attack, has no energy!" << std::endl;
        return;
    }
    this->energy--;
    std::cout << "ScavTrap " << this->name << " attacks " << target
              << ", causing " << this->damage << " points of damage!" << std::endl;
}

void ScavTrap::guardGate()
{
    std::cout << "ScavTrap " << this->name
              << " is now in Gatekeeper mode!" << std::endl;
}
