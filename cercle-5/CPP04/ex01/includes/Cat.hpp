/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:17:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal
{
	private:
		Brain* brain;
		static const Verbose verbose = FULL;

	public:
		Cat();
		Cat(const Cat& other);
		virtual ~Cat();
		Cat& operator=(const Cat& other);
		void makeSound() const;
};

std::ostream& operator<<(std::ostream& os, const Cat& obj);
