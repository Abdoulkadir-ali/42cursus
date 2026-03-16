/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 04:32:44 by abdoali          ###   ########.fr       */
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

Animal::~Animal(void)
{
	std::cout << "Destroying " <<this->type << std::endl;
}