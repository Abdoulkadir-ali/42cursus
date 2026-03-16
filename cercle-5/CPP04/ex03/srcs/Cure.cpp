/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 09:35:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 09:36:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cure.hpp"
#include "ICharacter.hpp"

Cure::Cure() : AMateria("Cure")
{
    std::cout << this->type << " default constructor called" << std::endl;
}

Cure::Cure(const Cure& other) : AMateria(other)
{
    std::cout << this->type << " copy constructor called" << std::endl;
}

Cure::~Cure()
{
    std::cout << this->type << " destructor called" << std::endl;
}

Cure& Cure::operator=(const Cure& other)
{
    (void)other;
    std::cout << this->type << " copy assignment operator called" << std::endl;
    return *this;
}

AMateria* Cure::clone() const
{
    return new Cure(*this);
}

void Cure::use(ICharacter& target)
{
    std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}