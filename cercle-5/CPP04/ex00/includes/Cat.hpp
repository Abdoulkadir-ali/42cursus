/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:06:29 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 18:11:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Animal.hpp"
#include "defines.hpp"

class Cat : public Animal
{
	private:
    	static const Verbose verbose = FULL;
    
  	public:
    	Cat();
    	Cat(const Cat &copycat);
    	~Cat();
    	Cat& operator=(const Cat& other);
    	void makeSound(void) const;
    	friend std::ostream& operator<<(std::ostream& os, const Cat& c);
};