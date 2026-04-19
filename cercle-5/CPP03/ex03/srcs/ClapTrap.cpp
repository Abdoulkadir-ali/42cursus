/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:44 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:23:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : name(""), hp(10), energy(10), damage(0)
{
    std::cout << "ClapTrap default constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
    : name(name), hp(10), energy(10), damage(0)
{
    std::cout << "ClapTrap " << this->name << " constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& c)
    : name(c.name), hp(c.hp), energy(c.energy), damage(c.damage)
{
    std::cout << "ClapTrap " << this->name << " copy constructor called" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& c)
{
    if (this != &c)
    {
        name   = c.name;
        hp     = c.hp;
        energy = c.energy;
        damage = c.damage;
    }
    return *this;
}

ClapTrap::~ClapTrap()
{
    std::cout << "ClapTrap " << this->name << " destructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (!this->hp)
    {
        std::cout << "ClapTrap " << this->name
                  << " can't attack, has no hit points!" << std::endl;
        return;
    }
    if (!this->energy)
    {
        std::cout << "ClapTrap " << this->name
                  << " can't attack, has no energy!" << std::endl;
        return;
    }
    this->energy--;
    std::cout << "ClapTrap " << this->name << " attacks " << target
              << ", causing " << this->damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (!this->hp)
    {
        std::cout << "ClapTrap " << this->name << " is already dead!" << std::endl;
        return;
    }
    if (this->hp <= amount)
        this->hp = 0;
    else
        this->hp -= amount;
    std::cout << "ClapTrap " << this->name << " took " << amount
              << " points of damage! HP left: " << this->hp << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (!this->hp)
    {
        std::cout << "ClapTrap " << this->name
                  << " can't repair, has no hit points!" << std::endl;
        return;
    }
    if (!this->energy)
    {
        std::cout << "ClapTrap " << this->name
                  << " can't repair, has no energy!" << std::endl;
        return;
    }
    this->energy--;
    if (this->hp > UINT_MAX - amount)
        this->hp = UINT_MAX;
    else
        this->hp += amount;
    std::cout << "ClapTrap " << this->name << " repaired itself for " << amount
              << " HP! HP: " << this->hp << std::endl;
}

const std::string& ClapTrap::getName() const
{
    return this->name;
}
