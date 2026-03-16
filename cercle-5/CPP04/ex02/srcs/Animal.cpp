/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 06:44:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 07:07:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Animal.hpp"


Animal::Animal(): name(""), type("Animal")
{}

Animal::Animal(const Animal& other)
{
    this->name = other.name;
    this->type = other.type;
}

Animal::~Animal() 
{}

Animal& Animal::operator=(const Animal& other)
{
    if (this != &other)
    {
        this->name = other.name;
        this->type = other.type;
    }
    return *this;
}

std::string Animal::getType() const
{return this->type;}

std::string Animal::getName() const
{return this->name;}

std::ostream& operator<<(std::ostream& os, const Animal& animal)
{
    os << "Animal <" << animal.getType() << ">, Name: " << animal.getName();
    return os;
}