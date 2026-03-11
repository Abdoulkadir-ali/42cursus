/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 16:33:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 17:40:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap()
    : type("ClapTrap"), hp(10), energy(10), damage(0)
{
    std::cout << this->type << " Constructor called" << std::endl;
}

ClapTrap::ClapTrap(const std::string& type, const unsigned int hp, const unsigned int energy, const unsigned int damage)
    : type(type), hp(hp), energy(energy), damage(damage)
{
    std::cout << this->type << " Parametrized constructor called" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap &c)
    : type(c.type), name(c.name), hp(c.hp), energy(c.energy), damage(c.damage)
{
    std::cout << this->type << " Copy constructor called" << std::endl;
}

ClapTrap::~ClapTrap()
{
	std::cout << this->type << " Desctructor called" << std::endl;
}

void ClapTrap::attack(const std::string& target)
{
    if (this->energy)
    {
        std::cout << this->type << this->name << " attacks " << target << ", causing " << this->damage << " points of damage!" << std::endl;
        this->energy--;
    }
    std::cout << this->type << this->name << " do not enough energy to launch attack" << std::endl;
}

void ClapTrap::takeDamage(const unsigned int damage)
{
    if (this->hp)
    {
        if (this->hp < damage)
        {
            this->hp = 0;
            std::cout << this->type << this->name << " took " << damage << " points of damage and died !" << std::endl;
        }
        else
        {
            this->hp = this->hp - damage;
            std::cout << this->type << this->name << " took " << damage << " points of damage!" << std::endl;
        }
        this->energy--;
    }
    else
        std::cout << this->type << this->name << " is already dead and can no longer take damage" << std::endl;
}

void ClapTrap::beRepaired(const unsigned int amount)
{
    if (this->energy)
    {
        std::cout << this->type << this->name << " repairs itself for " << amount << " amount!" << std::endl;
        this->energy--;
        if (this->hp < UINT_MAX - amount)
            this->hp += amount;
        else
            this->hp = UINT_MAX;
    }
    std::cout << this->type << this->name << " do not enough energy to repair itself" << std::endl;
}

const std::string &ClapTrap::getName(void) const { return this->name; }
const std::string &ClapTrap::getType(void) const { return this->type; }

std::ostream& operator<<(std::ostream& out, const ClapTrap& self)
{
    out << self.getType() << "instance : <" << self.getName() << ">" << std::endl;
    return out;
}