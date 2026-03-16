/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 06:29:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : name(""), type("Animal")
{
	std::cout << "Building " <<this->type << std::endl;
}

Animal::Animal(const Animal &c)
{
	
    this->name = c.name;
    this->type = c.type;
	std::cout << "Copying " <<this->type << std::endl;
}

Animal::~Animal()
{
    std::cout << "Killing " << this->type << std::endl;
}

Animal& Animal::operator=(const Animal &a)
{
    if (this != &a)
    {
        this->name = a.name;
        this->type = a.type;
    }
    return (*this);
}