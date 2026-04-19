/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:33:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:57:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : type("ClapTrap"), name(""), hp(10), max_hp(UINT_MAX), energy(10), damage(0)
{
    std::cout << this->type << " Constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
    : type("ClapTrap"), name(name), hp(10), max_hp(UINT_MAX), energy(10), damage(0)
{
    std::cout << this->type << " " << this->name << " Constructor called" << std::endl;
}

ClapTrap::ClapTrap(const unsigned int hp, const unsigned int energy, const unsigned int damage)
    : type("ClapTrap"), hp(hp), max_hp(UINT_MAX), energy(energy), damage(damage)
{
    std::cout << this->type << " Parametrized constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &c)
    : type(c.type), name(c.name), hp(c.hp), max_hp(c.max_hp), energy(c.energy), damage(c.damage)
{
    std::cout << this->type << " " << this->name << " Copy constructor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << this->type << " Desctructor called" << std::endl;
}

bool ClapTrap::isDead(bool verbose) const
{
    if (!this->hp)
    {
        if (verbose)
            std::cout << this->type << " " << this->name << " is dead!" << std::endl;
        return true;
    }
    return false;
}

bool ClapTrap::hasEnergy(bool verbose) const
{
    if (!this->energy)
    {
        if (verbose)
            std::cout << this->type << " " << this->name << " has no energy!" << std::endl;
        return false;
    }
    return true;
}

void ClapTrap::attack(const std::string& target)
{
    if (isDead(true) || !hasEnergy(true))
        return;
    this->energy--;
    std::cout << this->type << " " << this->name << " attacks " << target << ", causing " << this->damage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(const unsigned int damage)
{
    if (isDead(true))
        return;
    if (this->hp <= damage)
        this->hp = 0;
    else
        this->hp -= damage;
    std::cout << this->type << " " << this->name << " took " << damage << " points of damage! HP left: " << this->hp << std::endl;
}

void ClapTrap::beRepaired(const unsigned int amount)
{
    if (isDead(true) || !hasEnergy(true))
        return;
    this->energy--;
    if (this->hp > this->max_hp - amount)
        this->hp = this->max_hp;
    else
        this->hp += amount;
    std::cout << this->type << " " << this->name << " repaired itself for " << amount << " HP! HP: " << this->hp << std::endl;
}

const std::string &ClapTrap::getName(void) const { return this->name; }
const std::string &ClapTrap::getType(void) const { return this->type; }

std::ostream& operator<<(std::ostream& out, const ClapTrap& self)
{
    out << self.getType() << "instance : <" << self.getName() << ">" << std::endl;
    return out;
}