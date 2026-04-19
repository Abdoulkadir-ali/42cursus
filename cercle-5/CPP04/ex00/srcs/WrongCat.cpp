/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:36:03 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:36:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"

WrongCat::WrongCat()
{
	this->type = "WrongCat";
	if (verbose == FULL)
		std::cout << "WrongCat constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other)
{
	if (verbose == FULL)
		std::cout << "WrongCat copy constructor called" << std::endl;
	*this = other;
}

WrongCat::~WrongCat()
{
	if (verbose == FULL)
		std::cout << "WrongCat destructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other)
{
	if (verbose == FULL)
		std::cout << "WrongCat assignation operator called" << std::endl;
	if (this != &other)
		this->type = other.type;
	return *this;
}

void WrongCat::makeSound() const
{
	std::cout << "Wrong Meow" << std::endl;
}

std::ostream& operator<<(std::ostream& os, const WrongCat& obj)
{
	os << "WrongCat type: " << obj.getType();
	return os;
}
