/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongAnimal.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:11:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:42:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include "defines.hpp"

class WrongAnimal
{
    private:
        static const Verbose verbose = FULL;

    protected:
        std::string type;

    public:
        WrongAnimal(void);
        WrongAnimal(const WrongAnimal &a);
        virtual ~WrongAnimal();
        WrongAnimal& operator=(const WrongAnimal& other);
        void        makeSound(void) const;
        std::string getType(void) const;
        friend std::ostream& operator<<(std::ostream& os, const WrongAnimal& a);
};
