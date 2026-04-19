/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:23:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 14:00:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <climits>

class ClapTrap
{
protected:
    std::string     name;
    unsigned int    hp;
    unsigned int    max_hp;
    unsigned int    energy;
    unsigned int    damage;

public:
    ClapTrap();
    ClapTrap(const std::string& name);
    ClapTrap(const ClapTrap& c);
    ClapTrap& operator=(const ClapTrap& c);
    ~ClapTrap();

    void attack(const std::string& target);
    void takeDamage(unsigned int amount);
    void beRepaired(unsigned int amount);
    bool isDead(bool verbose = false) const;
    bool hasEnergy(bool verbose = false) const;

    const std::string& getName() const;
};
