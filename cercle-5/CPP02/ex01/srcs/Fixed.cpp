/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/11 04:44:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
    : value(0)
{
	std::cout << "Constructor called" << std::endl;
}

Fixed::Fixed(int value)
    : value(0)
{
	std::cout << "Constructor Int called" << std::endl;
	this->value = value << this->bits;
}

Fixed::Fixed(float value)
    : value(0)
{
	std::cout << "Constructor Int called" << std::endl;
	this->value = static_cast<int>(roundf(value * (1 << this->bits)));
}

Fixed::~Fixed()
{
	std::cout << "Desctructor called" << std::endl;
}

int Fixed::getRawBits(void) const
{
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
	if (this != &c)
		this->value = c.value;
	return (*this);
}

float Fixed::toFloat(void) const
{
	return static_cast<float>(this->value) / (1 << this->bits);
}

int Fixed::toInt(void) const
{
	return static_cast<int>(this->value) >> this->bits;
}

std::ostream& operator<<(std::ostream& out, const Fixed &c)
{
	out << c.toFloat();
	return (out);
}