/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 06:25:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() : Animal()
{
    this->type = "Cat";
    this->name = "";
    this->brain = new Brain();
    std::cout << "Building " <<this->type << std::endl;
}

Cat::Cat(const Cat& copyCat) : Animal(copyCat)
{   
    this->name = copyCat.name;
    this->type = copyCat.type;
    if (this->brain)
        delete this->brain;
    if (copyCat.brain)
        this->brain = new Brain(*copyCat.brain);
    else
        this->brain = NULL;
}

Cat::~Cat()
{
    if (this->brain)
        delete this->brain;
    std::cout << "Killing " <<this->type << std::endl;
}

void Cat::makeSound(void)
{
    std::cout << "<" << this->type << ">: Meow" << std::endl;
}