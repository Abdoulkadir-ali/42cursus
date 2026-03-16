/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 07:03:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Animal
{
    protected:
        std::string name;
        std::string type;
        /* Making the constructor private to avoid instantiation*/


    public:
        Animal();
        Animal(const Animal &a);
        virtual ~Animal();
        virtual void makeSound(void) = 0;
        Animal& operator=(const Animal &a);
        std::string getType() const;
        std::string getName() const;
};

std::ostream& operator<<(std::ostream& os, const Animal& animal);