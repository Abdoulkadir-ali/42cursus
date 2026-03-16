/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:42:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 14:47:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include <iostream>

Character::Character()
    : name("default"), inventory(NULL)
{
}

Character::Character(const std::string& name)
    : name(name), inventory(NULL)
{
}

Character::Character(const Character& other)
    : name(other.name), inventory(other.inventory)
{
}

Character& Character::operator=(const Character& other)
{
    if (this == &other)
        return *this;

    name = other.name;
    inventory = other.inventory;
    return *this;
}

Character::~Character()
{
}

std::string const & Character::getName() const
{
    return name;
}

void Character::equip(AMateria* m)
{
    inventory->equip(m);
}

void Character::unequip(int idx)
{
    inventory->unequip(idx);
}

void Character::use(int idx, ICharacter &target)
{
    const Materia* m = inventory->getItem(idx);
    if (m)
        m->use(static_cast<Materia>(target));
}
