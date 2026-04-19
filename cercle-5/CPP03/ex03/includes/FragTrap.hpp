/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:23:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ClapTrap.hpp"

/* virtual inheritance: ensures only ONE ClapTrap subobject
   exists when DiamondTrap inherits from both ScavTrap and FragTrap */
class FragTrap : virtual public ClapTrap
{
public:
    FragTrap();
    FragTrap(const std::string& name);
    FragTrap(const FragTrap& c);
    FragTrap& operator=(const FragTrap& c);
    ~FragTrap();

    void highFivesGuys();
};
