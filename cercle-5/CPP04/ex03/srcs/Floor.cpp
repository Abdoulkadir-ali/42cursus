/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Floor.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 02:13:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Floor.hpp"

Floor::Floor() : lastIndex(-1)
{
	for (size_t i = 0; i < maxSize; i++)
		items[i] = 0;
}

Floor::Floor(const Floor& other) : Inventory(other), lastIndex(-1)
{
	for (size_t i = 0; i < maxSize; i++)
		items[i] = 0;
	copyFrom(other);
}

Floor::~Floor()
{
	clear();
}

Floor& Floor::operator=(const Floor& other)
{
	if (this != &other)
	{
		Inventory::operator=(other);
		clear();
		copyFrom(other);
	}
	return *this;
}

void Floor::drop(AMateria* m)
{
	if (!m)
		return ;
	if (lastIndex + 1 < (int)maxSize)
		items[++lastIndex] = m;
	else
		delete m;
}

void Floor::clear()
{
	for (int i = 0; i <= lastIndex; i++)
	{
		delete items[i];
		items[i] = 0;
	}
	lastIndex = -1;
}

void Floor::copyFrom(const Floor& other)
{
	for (int i = 0; i <= other.lastIndex; i++)
		items[i] = other.items[i] ? other.items[i]->clone() : 0;
	lastIndex = other.lastIndex;
}
