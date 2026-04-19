/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:33:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 14:00:22 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : name(""), hp(10), max_hp(UINT_MAX), energy(10), damage(0)
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
    : name(name), hp(10), max_hp(UINT_MAX), energy(10), damage(0)
{
    std::cout << "ClapTrap " << this->name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& c)
    : name(c.name), hp(c.hp), max_hp(c.max_hp), energy(c.energy), damage(c.damage)
{
    std::cout << "ClapTrap " << this->name << " copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& c)
{
    if (this != &c)
    {
        name   = c.name;
        hp     = c.hp;
        max_hp = c.max_hp;
        energy = c.energy;
        damage = c.damage;
    }
    return *this;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " destructor called" << std::endl;
}

bool ClapTrap::isDead(bool verbose) const
{
    if (!this->hp)
    {
        if (verbose)
            std::cout << "ClapTrap " << this->name << " is dead!" << std::endl;
        return true;
    }
    return false;
}

bool ClapTrap::hasEnergy(bool verbose) const
{
    if (!this->energy)
    {
        if (verbose)
            std::cout << "ClapTrap " << this->name << " has no energy!" << std::endl;
        return false;
    }
    return true;
}

void ClapTrap::attack(const std::string& target)
{
    if (isDead(true) || !hasEnergy(true))
        return;
    this->energy--;
    std::cout << "ClapTrap " << this->name << " attacks " << target
              << ", causing " << this->damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (isDead(true))
        return;
    if (this->hp <= amount)
        this->hp = 0;
    else
        this->hp -= amount;
    std::cout << "ClapTrap " << this->name << " took " << amount
              << " points of damage! HP left: " << this->hp << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (isDead(true) || !hasEnergy(true))
        return;
    this->energy--;
    if (this->hp > this->max_hp - amount)
        this->hp = this->max_hp;
    else
        this->hp += amount;
    std::cout << "ClapTrap " << this->name << " repaired itself for " << amount
              << " HP! HP: " << this->hp << std::endl;
}

const std::string& ClapTrap::getName() const
{
    return this->name;
}
