/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:23:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"

FragTrap::FragTrap()
    : ClapTrap()
{
    this->hp     = 100;
    this->energy = 100;
    this->damage = 30;
    std::cout << "FragTrap default constructor called" << std::endl;
}

FragTrap::FragTrap(const std::string& name)
    : ClapTrap(name)
{
    this->hp     = 100;
    this->energy = 100;
    this->damage = 30;
    std::cout << "FragTrap " << this->name << " constructor called" << std::endl;
}

FragTrap::FragTrap(const FragTrap& c)
    : ClapTrap(c)
{
    std::cout << "FragTrap " << this->name << " copy constructor called" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& c)
{
    if (this != &c)
        ClapTrap::operator=(c);
    return *this;
}

FragTrap::~FragTrap()
{
    std::cout << "FragTrap " << this->name << " destructor called" << std::endl;
}

void FragTrap::highFivesGuys()
{
    std::cout << "FragTrap " << this->name
              << " requests a high five! \\o/" << std::endl;
}
