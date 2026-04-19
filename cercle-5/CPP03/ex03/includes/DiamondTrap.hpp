/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:23:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap
{
private:
    std::string name; // DiamondTrap's own name (shadows ClapTrap::name)

public:
    DiamondTrap();
    DiamondTrap(const std::string& name);
    DiamondTrap(const DiamondTrap& c);
    DiamondTrap& operator=(const DiamondTrap& c);
    ~DiamondTrap();

    using ScavTrap::attack; // use ScavTrap's attack

    void whoAmI();
};
