/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:13:51 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 04:39:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"

Fixed::Fixed()
    : value(0)
{
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(int value)
    : value(0)
{
	std::cout << "Int constructor called" << std::endl;
	this->value = value << this->bits;
}

Fixed::Fixed(float value)
    : value(0)
{
	std::cout << "Float constructor called" << std::endl;
	this->value = static_cast<int>(roundf(value * (1 << this->bits)));
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
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
	std::cout << "Copy assignment operator called" << std::endl;
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

// Comparison operators
bool Fixed::operator>(const Fixed& other) const
{
    return this->value > other.value;
}
bool Fixed::operator<(const Fixed& other) const
{
    return this->value < other.value;
}
bool Fixed::operator>=(const Fixed& other) const
{
    return this->value >= other.value;
}
bool Fixed::operator<=(const Fixed& other) const
{
    return this->value <= other.value;
}
bool Fixed::operator==(const Fixed& other) const
{
    return this->value == other.value;
}
bool Fixed::operator!=(const Fixed& other) const
{
    return this->value != other.value;
}

// Arithmetic operators
Fixed Fixed::operator+(const Fixed& other) const
{
    Fixed result;
    result.value = this->value + other.value;
    return result;
}
Fixed Fixed::operator-(const Fixed& other) const
{
    Fixed result;
    result.value = this->value - other.value;
    return result;
}
Fixed Fixed::operator*(const Fixed& other) const
{
    Fixed result;
    result.value = (this->value * other.value) >> bits;
    return result;
}
Fixed Fixed::operator/(const Fixed& other) const
{
    Fixed result;
    result.value = (this->value << bits) / other.value;
    return result;
}

// Pre-increment
Fixed& Fixed::operator++()
{
    ++this->value;
    return *this;
}
// Post-increment
Fixed Fixed::operator++(int)
{
    Fixed temp = *this;
    ++this->value;
    return temp;
}
// Pre-decrement
Fixed& Fixed::operator--()
{
    --this->value;
    return *this;
}
// Post-decrement
Fixed Fixed::operator--(int)
{
    Fixed temp = *this;
    --this->value;
    return temp;
}

Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    return (a < b) ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    return (a < b) ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    return (a > b) ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    return (a > b) ? a : b;
}
