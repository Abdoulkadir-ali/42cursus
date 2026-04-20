/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Animal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:05:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:18:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "defines.hpp"

class Animal
{
	private:
		static const Verbose verbose = FULL;

	protected:
		std::string type;

	public:
		Animal();
		Animal(const Animal& other);
		virtual ~Animal();
		Animal& operator=(const Animal& other);

		virtual void makeSound() const = 0;
		std::string getType() const;
};

std::ostream& operator<<(std::ostream& os, const Animal& obj);
