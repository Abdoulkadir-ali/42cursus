/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 07:04:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() : Animal()
{
    this->type = "Dog";
    this->name = "Dogminette";
    this->brain = new Brain();
    std::cout << "Building " <<this->type << std::endl;
}

Dog::Dog(const Dog& copyDog) : Animal(copyDog)
{
    this->name = copyDog.name;
    this->type = copyDog.type;
    if (this->brain)
        delete this->brain;
    if (copyDog.brain)
        this->brain = new Brain(*copyDog.brain);
    else
        this->brain = NULL; 
}

Dog::~Dog()
{
    if (this->brain)
        delete this->brain;
    std::cout << "Killing " <<this->type << std::endl;
}

void Dog::makeSound(void)
{
    std::cout << "<" << this->type << ">: Bark" << std::endl;
}


Dog& Dog::operator=(const Dog& other)
{
    if (this != &other)
    {
        Animal::operator=(other);
        if (this->brain)
            delete this->brain;
        if (other.brain)
            this->brain = new Brain(*other.brain);
        else
            this->brain = NULL;
    }
    return *this;
}