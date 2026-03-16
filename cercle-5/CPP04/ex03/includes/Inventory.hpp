/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:46:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 11:54:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "AMateria.hpp"
#include "ICharacter.hpp"
#include <vector>

class   BInventory : public ICharacter
{
    protected:
        std::string type = "Inventory";
        unsigned int capacity = 10000;
        unsigned int usage = 0;
        std::vector<AMateria> items;
        
    public:
        BInventory();
        ~BInventory();
        BInventory(const BInventory &f);
        
        void equip(AMateria* m);
        void unequip(int idx);

        
        void extract(const BInventory& other);
        const AMateria* getItem(unsigned int idx);
        bool isMaxCapacity(bool Verbose);
        void PrintCapacity(bool percentage);
        bool isEmpty(bool Verbose);
};

extern BInventory g_floor;

class Inventory : public BInventory
{
    private:
        BInventory *g_floor;
        
    public:
        Inventory();
        ~Inventory();
        Inventory(const Inventory& f);
        void unequip(int idx);
};
