/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:33:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:36:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal")
{
	if (verbose == FULL)
		std::cout << "WrongAnimal constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other)
{
	if (verbose == FULL)
		std::cout << "WrongAnimal copy constructor called" << std::endl;
	*this = other;
}

WrongAnimal::~WrongAnimal()
{
	if (verbose == FULL)
		std::cout << "WrongAnimal destructor called" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other)
{
	if (verbose == FULL)
		std::cout << "WrongAnimal assignation operator called" << std::endl;
	if (this != &other)
		this->type = other.type;
	return *this;
}

void WrongAnimal::makeSound() const
{
	std::cout << "* WrongAnimal sound *" << std::endl;
}

std::string WrongAnimal::getType() const
{
	return this->type;
}

std::ostream& operator<<(std::ostream& os, const WrongAnimal& obj)
{
	os << "WrongAnimal type: " << obj.getType();
	return os;
}
