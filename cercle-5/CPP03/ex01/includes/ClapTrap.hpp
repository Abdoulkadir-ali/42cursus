/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:14:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 17:37:42 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <climits>

class ClapTrap
{
    protected:
        std::string     type;
    private:
        std::string     name;
        unsigned int    hp;
        unsigned int    energy;
        unsigned int    damage;
        
    public:
        ClapTrap();
        ClapTrap(const ClapTrap &c);
        ClapTrap(const std::string& type, const unsigned int hp, const unsigned int energy, const unsigned int attack);
        ~ClapTrap();
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        const std::string &getName(void) const;
        const std::string &getType(void) const;
};

std::ostream& operator<<(std::ostream& out, const ClapTrap& ClapTrap);