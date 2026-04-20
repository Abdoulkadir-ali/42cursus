/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   WrongCat.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:55:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:16:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal
{
    private:
        static const Verbose verbose = FULL;
        
    public:
		WrongCat();
		WrongCat(const WrongCat& other);
		virtual ~WrongCat();
		WrongCat& operator=(const WrongCat& other);
        void makeSound() const;
};

std::ostream& operator<<(std::ostream& os, const WrongCat& obj);
