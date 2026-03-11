/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:26:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:53:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Weapon.hpp"

Weapon::Weapon(std::string type, int minDamage, int maxDamage) 
    : _type(type), _minDamage(minDamage), _maxDamage(maxDamage)
{
    if (_minDamage > _maxDamage)
    {
        int temp = _minDamage;
        _minDamage = _maxDamage;
        _maxDamage = temp;
    }
}

Weapon::Weapon(void) : _type("default"), _minDamage(5), _maxDamage(10)
{
}

Weapon::~Weapon(void)
{
}

const std::string &Weapon::getType(void) const
{
    return (this->_type);
}

void Weapon::setType(std::string type)
{
    this->_type = type;
}

int Weapon::getDamage(void) const
{
    return (this->_minDamage + (rand() % (this->_maxDamage - this->_minDamage + 1)));
}

