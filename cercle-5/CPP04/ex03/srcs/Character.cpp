/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:07:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 02:20:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"

Character::Character(std::string const& name) : name(name)
{
	if (verbose == FULL)
		std::cout << "Character " << name << " created" << std::endl;
}

Character::Character(const Character& other) : name(other.name), inventory(other.inventory), floor(other.floor)
{
	if (verbose == FULL)
		std::cout << "Character " << name << " copied" << std::endl;
}

Character::~Character()
{
	if (verbose == FULL)
		std::cout << "Character " << name << " destroyed" << std::endl;
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		name = other.name;
		inventory = other.inventory;
		floor = other.floor;
	}
	return *this;
}

std::string const& Character::getName() const
{
	return name;
}

void Character::equip(AMateria* m)
{
	inventory.addMateria(m);
}

void Character::unequip(int idx)
{
	floor.drop(inventory.removeMateria(idx));
}

void Character::use(int idx, ICharacter& target)
{
	AMateria* m = inventory.getMateria(idx);
	if (m)
		m->use(target);
}

Inventory Character::getInventory() const
{
	return this->inventory;
}

std::ostream& operator<<(std::ostream& os, const Character& obj)
{
	os << "Character " << obj.getName() << " with inventory:" << obj.getInventory();
	return os;
}
