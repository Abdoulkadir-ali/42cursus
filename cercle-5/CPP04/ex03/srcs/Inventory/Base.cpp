/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 10:35:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 11:53:56 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Inventory.hpp"

BInventory::BInventory() : ICharacter()
{
    for (int i = 0; i < this->capacity; i++)
        this->items[i] = NULL;
    std::cout << this->type << " default constructor called" << std::endl;
}

BInventory::~BInventory()
{
    for (unsigned int i = 0; i < this->usage; ++i)
    {
        delete this->getItem(i);
        this->usage--;
    }
}

BInventory::BInventory(const BInventory& other) : ICharacter(other)
{
    if (this != other)
    {
        for (unsigned int i = 0; i < this->usage; ++i)
            this->unequip(i);
        this->capacity = other.capacity;
        for (unsigned int i = 0; i < this->usage; ++i)
            this->equip(other.getItem(i));
    }
    std::cout << this->type << " copy constructor called" << std::endl;
}

BInventory& BInventory::operator=(const BInventory& other)
{
    if (this != &other)
    {
        for (unsigned int i = 0; i < this->usage; i++)
            delete this->items[i];
        
        this->capacity = other.capacity;
        this->usage = other.usage;
        for (unsigned int i = 0; i < other.usage; i++)
            this->items[i] = other.items[i] ? other.items[i]->clone() : NULL;
    }
    return *this;
}

BInventory::~BInventory()
{
    std::cout << this->type << " destructor called" << std::endl;
}

BInventory& BInventory::operator=(const BInventory& other)
{
    return this.extract(other);
}

BInventory* BInventory::getItem(unsigned int idx) const
{
    if (idx > this->usage)
    {
        std::cout << "No item located at index " << idx << std::endl;
        return NULL;
    }
    return this->items[idx];
}

BInventory* BInventory::clone() const
{
    return new BInventory(*this);
}

void BInventory::extract(const BInventory& other)
{
    for (unsigned int i = 0; i < this->usage; ++i)
        this->unequip(i);
    for (unsigned int i = 0; i < this->usage; ++i)
        this->equip(other.getItem(i));
}

void    BInventory::PrintCapacity(bool percentage)
{
    std::cout << "Current usage : (" this->usage << "/" << this->capacity << ")";
    if (percentage)
        std::cout << (this->usage * 100) / this->capacity << " %" << std::endl;
    std::endl;
}

bool BInventory::isMaxCapacity(bool Verbose)
{
    bool b;
    
    b = this->usage >= this->capacity;
    if (Verbose)
        std::cout << this->type << " has reached maximum capacity" << std::endl;
}

bool BInventory::isEmpty(bool Verbose)
{
    bool b;
    
    b = this->usage;
    if (Verbose)
        std::cout << this->type << " is empty" << std::endl;
}

void BInventory::equip(AMateria& item)
{
    if (!item)
        return;
    if (!this.isMaxCapacity(true))
    {
        this->BInventory.equip();
        this->items[this->usage + 1] = item;
        this->usage++;
    }
}

void BInventory::unequip(AMateria& item)
{
    if (this.isEmpty(true))
    {
        this->items.delete(idx);
        this->usage--;
    }
}

void Inventory::use(ICharacter& target)
{
    (void)idx;
    (void)target;
    std::cout << "Use not implemented in this class" << this << std::endl;
}