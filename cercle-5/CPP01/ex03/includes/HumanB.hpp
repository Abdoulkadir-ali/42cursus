/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanB.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:36:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:48:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Human.hpp"

class HumanB : public Human
{
public:
    HumanB(std::string name);
    ~HumanB(void);
  
    void setWeapon(Weapon& weapon);
};