/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:07:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:44:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Inventory.hpp"

Inventory::Inventory()
{
	for (size_t i = 0; i < maxSize; i++)
		materias[i] = 0;
	if (this->verbose == FULL)
		std::cout << "Inventory created" << std::endl;
}

Inventory::Inventory(const Inventory& other)
{
	for (size_t i = 0; i < maxSize; i++)
		materias[i] = 0;
	*this = other;
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < maxSize; i++)
		delete materias[i];
	if (this->verbose == FULL)
		std::cout << "Inventory destroyed" << std::endl;
}

Inventory& Inventory::operator=(const Inventory& other)
{
	if (this != &other)
	{
		for (size_t i = 0; i < maxSize; i++)
			delete materias[i];
		for (size_t i = 0; i < maxSize; i++)
			materias[i] = other.materias[i] ? other.materias[i]->clone() : 0;
	}
	return *this;
}

void Inventory::addMateria(AMateria* m)
{
	if (!m)
		return ;
	for (size_t i = 0; i < maxSize; i++)
	{
		if (!materias[i])
		{
			materias[i] = m;
			return ;
		}
	}
}

void Inventory::removeMateria(int idx)
{
	if (idx >= 0 && idx < (int)maxSize)
		materias[idx] = 0;
}

AMateria* Inventory::getMateria(int idx) const
{
	if (idx >= 0 && idx < (int)maxSize)
		return materias[idx];
	return 0;
}

size_t Inventory::getCount() const
{
	size_t count = 0;

	for (size_t i = 0; i < maxSize; i++)
	{
		if (materias[i])
			count++;
	}
	return count;
}

std::ostream& operator<<(std::ostream& os, const Inventory& obj)
{
	os << "Inventory (" << obj.getCount() << "/4): " << std::endl;
	for (size_t i = 0; i < 4; i++)
	{
		if (obj.getMateria(i))
			os << "  [" << i << "] " << obj.getMateria(i)->getType() << std::endl;
	}
	return os;
}
