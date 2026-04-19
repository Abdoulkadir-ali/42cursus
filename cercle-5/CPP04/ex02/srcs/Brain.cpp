/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:38:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:38:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
{
	if (verbose == FULL)
		std::cout << "Brain constructor called" << std::endl;
}

Brain::Brain(const Brain& other)
{
	if (verbose == FULL)
		std::cout << "Brain copy constructor called" << std::endl;
	*this = other;
}

Brain::~Brain()
{
	if (verbose == FULL)
		std::cout << "Brain destructor called" << std::endl;
}

Brain& Brain::operator=(const Brain& other)
{
	if (verbose == FULL)
		std::cout << "Brain assignation operator called" << std::endl;
	if (this != &other)
	{
		for (int i = 0; i < 100; i++)
			ideas[i] = other.ideas[i];
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Brain& obj)
{
	(void)obj;
	os << "Brain containing ideas";
	return os;
}
