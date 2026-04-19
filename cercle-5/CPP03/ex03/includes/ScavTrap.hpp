/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:23:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClapTrap.hpp"

/* virtual inheritance: ensures only ONE ClapTrap subobject
   exists when DiamondTrap inherits from both ScavTrap and FragTrap */
class ScavTrap : virtual public ClapTrap
{
public:
    ScavTrap();
    ScavTrap(const std::string& name);
    ScavTrap(const ScavTrap& c);
    ScavTrap& operator=(const ScavTrap& c);
    ~ScavTrap();

    void attack(const std::string& target);
    void guardGate();
};
