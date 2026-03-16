/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:48:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 14:48:36 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Inventory.hpp"

Inventory::Inventory() : BInventory()
{
    std::cout << this->type << " default constructor called" << std::endl;
}

Inventory::~Inventory()
{
    for (unsigned int i = 0; i < this->usage; ++i)
    {
        delete this->getItem(i);
        this->usage--;
    }
}

Inventory::Inventory(const Inventory& other) : BInventory(other)
{
    if (this != &other)
    {
        for (unsigned int i = 0; i < this->usage; ++i)
        this->unequip(i);
        this->capacity = other.capacity;
        for (unsigned int i = 0; i < this->usage; ++i)
            this->equip(other.getItem(i));
    }
    std::cout << this->type << " copy constructor called" << std::endl;
}

Inventory::~Inventory()
{
    std::cout << this->type << " destructor called" << std::endl;
}

void Inventory::unequip(int idx)
{
    if (idx < 0)
    {
        std::cout << "CRITICAL : Can't get negative index item : <" << idx << ">" std::endl;
        return;
    }
    if (!this.isEmpty(true))
    {
        if (this->floor.isMaxCapacity())
        {
            std::cout << "CRITICAL : Can't drop item floor is full" << std::endl;
            return;
        }
        this->floor.equip(this->items[idx]);
        this->BInventory.unequip();
    }
}