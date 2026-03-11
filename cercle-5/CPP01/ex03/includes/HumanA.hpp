/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HumanA.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:36:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:48:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Human.hpp"

class HumanA : public Human
{
public:
    HumanA(std::string name, Weapon& weapon);
    ~HumanA(void);

    // Using base class attack
};