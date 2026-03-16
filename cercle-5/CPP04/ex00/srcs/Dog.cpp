/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 04:32:33 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
    this->type = "Dog";
    this->name = "";
    std::cout << "Building " <<this->type << std::endl;
}

Dog::Dog(const Dog& copyDog) : Animal(copyDog)
{
    this->name = copyDog.name;
    this->type = copyDog.type;
}

Dog::~Dog()
{
    std::cout << "Killing " <<this->type << std::endl;
}

void Dog::makeSound(void)
{
    std::cout << "<" << this->type << ">: Bark" << std::endl;
}