/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:36:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:53:59 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <cstdlib>

class Weapon
{
public:
    Weapon(std::string type, int minDamage = 10, int maxDamage = 20);
    Weapon(void);
    ~Weapon(void);

    const std::string &getType(void) const;
    void setType(std::string type);
    int getDamage(void) const; // Returns random damage between min and max
    
private:
    std::string _type;
    int _minDamage;
    int _maxDamage;
};