/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:07:45 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 18:15:07 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Inventory.hpp"

Inventory::Inventory() : maxSize(4)
{
	if (this->verbose == FULL)
		std::cout << "Inventory created" << std::endl;
}

Inventory::Inventory(const Inventory& other)
{
	*this = other;
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < materias.size(); i++)
		delete materias[i];
	if (this->verbose == FULL)
		std::cout << "Inventory destroyed" << std::endl;
}
Inventory& Inventory::operator=(const Inventory& other)
{
	if (this != &other)
	{
		for (size_t i = 0; i < materias.size(); i++)
			delete materias[i];
		materias.clear();
		for (size_t i = 0; i < other.materias.size(); i++)
			materias.push_back(other.materias[i]->clone());
	}
	return *this;
}

void Inventory::addMateria(AMateria* m)
{
	if (m && materias.size() < maxSize)
		materias.push_back(m);
}

void Inventory::removeMateria(int idx)
{
	if (idx >= 0 && idx < (int)materias.size())
		materias.erase(materias.begin() + idx);
}

AMateria* Inventory::getMateria(int idx) const
{
	if (idx >= 0 && idx < (int)materias.size())
		return materias[idx];
	return 0;
}

std::ostream& operator<<(std::ostream& os, const Inventory& obj)
{
	os << "Inventory (" << obj.materias.size() << "/" << obj.maxSize << "): " << std::endl;
	for (size_t i = 0; i < obj.materias.size(); i++)
		os << "  [" << i << "] " << obj.materias[i]->getType() << std::endl;
	return os;
}
