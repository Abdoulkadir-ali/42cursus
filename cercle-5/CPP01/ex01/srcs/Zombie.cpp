/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:43:41 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/02 19:13:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie(std::string name) : _name(name)
{
}

Zombie::Zombie(void) : _name("")
{
}

Zombie::~Zombie(void)
{
    std::cout << this->_name << ": is dead" << std::endl;
}

Zombie::Zombie(const Zombie &src)
{
    *this = src;
}

void Zombie::announce(void)
{
    std::cout << this->_name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name)
{
    this->_name = name;
}

Zombie* newZombie(std::string name)
{
    return (new Zombie(name));
}

void randomChump(std::string name)
{
    Zombie z(name);
    z.announce();
}
