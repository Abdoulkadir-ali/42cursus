/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:24:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:24:01 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap()
    : ClapTrap("_clap_name"),
      ScavTrap(),
      FragTrap(),
      name("")
{
    this->hp     = FragTrap::hp;
    this->energy = ScavTrap::energy;
    this->damage = FragTrap::damage;
    std::cout << "DiamondTrap default constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name)
    : ClapTrap(name + "_clap_name"),
      ScavTrap(name),
      FragTrap(name),
      name(name)
{
    
    this->hp     = FragTrap::hp;
    this->energy = ScavTrap::energy;
    this->damage = FragTrap::damage;
    std::cout << "DiamondTrap " << this->name << " constructor called" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& c)
    : ClapTrap(c),
      ScavTrap(c),
      FragTrap(c),
      name(c.name)
{
    std::cout << "DiamondTrap " << this->name << " copy constructor called" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& c)
{
    if (this != &c)
    {
        ClapTrap::operator=(c);
        name = c.name;
    }
    return *this;
}

DiamondTrap::~DiamondTrap()
{
    std::cout << "DiamondTrap " << this->name << " destructor called" << std::endl;
}

void DiamondTrap::whoAmI()
{
    std::cout << "DiamondTrap name: " << this->name
              << " | ClapTrap name: " << ClapTrap::getName() << std::endl;
}
