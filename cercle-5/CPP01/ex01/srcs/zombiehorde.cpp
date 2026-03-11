/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zombiehorde.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:06:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:14:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie* zombieHorde( int n, std::string name )
{
    Zombie *horde = new Zombie[n];

    for (int i = 0; i < n; i++)
    {
        horde[i].setName(name);
        horde[i].announce();
    }
    return horde;
}