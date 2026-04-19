/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:37:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:37:34 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"

Animal::Animal() : type("Animal")
{
	if (verbose == FULL)
		std::cout << "Animal constructor called" << std::endl;
}

Animal::Animal(const Animal& other)
{
	if (verbose == FULL)
		std::cout << "Animal copy constructor called" << std::endl;
	*this = other;
}

Animal::~Animal()
{
	if (verbose == FULL)
		std::cout << "Animal destructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& other)
{
	if (verbose == FULL)
		std::cout << "Animal assignation operator called" << std::endl;
	if (this != &other)
		this->type = other.type;
	return *this;
}

void Animal::makeSound() const
{
	std::cout << "* Animal sound *" << std::endl;
}

std::string Animal::getType() const
{
	return this->type;
}

std::ostream& operator<<(std::ostream& os, const Animal& obj)
{
	os << "Animal type: " << obj.getType();
	return os;
}
