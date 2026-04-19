/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 04:21:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
    : value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (value);
}

void Fixed::setRawBits(int const raw)
{
	this->value = raw;
}

Fixed::Fixed(const Fixed &c)
{
	std::cout << "Copy constructor called" << std::endl;
	this->value = c.value;
}

Fixed &Fixed::operator=(const Fixed &c)
{
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &c)
		this->value = c.value;
	return (*this);
}