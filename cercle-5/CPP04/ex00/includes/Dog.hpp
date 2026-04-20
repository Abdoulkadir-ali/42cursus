/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:35:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:16:26 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "Animal.hpp"

class Dog : public Animal
{
	private:
		static const Verbose verbose = FULL;

	public:
		Dog();
		Dog(const Dog& other);
		virtual ~Dog();
		Dog& operator=(const Dog& other);
		void makeSound() const;
};

std::ostream& operator<<(std::ostream& os, const Dog& obj);
