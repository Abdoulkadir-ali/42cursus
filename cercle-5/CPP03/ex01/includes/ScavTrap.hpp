/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:14:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 17:44:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <climits>
#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap
{
    public:
        ScavTrap();
        ScavTrap(const unsigned int hp, const unsigned int energy, const unsigned int damage);
        ~ScavTrap();
        void attack(const std::string& target);
        void guardGate(void);
    protected:
        std::string     type;
    private:
        std::string     name;
        unsigned int    hp;
        unsigned int    energy;
        unsigned int    damage;
};