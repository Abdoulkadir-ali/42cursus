/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:36:34 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 00:56:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Weapon
{
public:
    Weapon(std::string type);
    ~Weapon(void);

    const std::string &getType(void) const;
    void setType(std::string type);

private:
    std::string _type;
};