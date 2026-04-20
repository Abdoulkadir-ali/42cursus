/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:16:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "defines.hpp"

class Animal
{
    private:
        static const Verbose verbose = FULL;

    protected:
        std::string name;
        std::string type;
        

    public:
        Animal(void);
        Animal(const Animal &a);
        virtual ~Animal();
        Animal& operator=(const Animal& other);
        virtual void makeSound(void) const;
        std::string  getType(void) const;
};

std::ostream& operator<<(std::ostream& os, const Animal& a);