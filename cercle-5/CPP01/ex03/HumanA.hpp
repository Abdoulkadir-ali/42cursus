/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:36:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 00:56:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Weapon.hpp"
#include <iostream>

class HumanA
{
public:
    HumanA(std::string name, Weapon &weapon);
    ~HumanA(void);

    void attack(void) const;

private:
    std::string _name;
    Weapon      &_weapon;
};