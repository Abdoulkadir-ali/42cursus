/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Human.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:36:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:53:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "Weapon.hpp"
#include <cstdlib>
#include <ctime>
class Human
{
public:
    Human(std::string name, int hp = 100);
    virtual ~Human(void);

    void attack(Human &target);
    void takeDamage(int amount);
    const std::string &getName(void) const;
    virtual void attack(void);

protected:
    std::string _name;
    int _hp;
    Weapon *_weapon;
};