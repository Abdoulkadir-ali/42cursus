/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:16:48 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:24:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (size_t i = 0; i < maxLearned; i++)
		templates[i] = 0;
	if (verbose == FULL)
		std::cout << "MateriaSource constructor called" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	for (size_t i = 0; i < maxLearned; i++)
		templates[i] = 0;
	if (verbose == FULL)
		std::cout << "MateriaSource copy constructor called" << std::endl;
	*this = other;
}

MateriaSource::~MateriaSource()
{
	for (size_t i = 0; i < maxLearned; i++)
		delete templates[i];
	if (verbose == FULL)
		std::cout << "MateriaSource destructor called" << std::endl;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	if (verbose == FULL)
		std::cout << "MateriaSource assignation operator called" << std::endl;
	if (this != &other)
	{
		for (size_t i = 0; i < maxLearned; i++)
			delete templates[i];
		for (size_t i = 0; i < maxLearned; i++)
			templates[i] = other.templates[i] ? other.templates[i]->clone() : 0;
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
	if (!m)
		return ;
	for (size_t i = 0; i < maxLearned; i++)
	{
		if (!templates[i])
		{
			templates[i] = m;
			return ;
		}
	}
}

AMateria* MateriaSource::createMateria(std::string const& type)
{
	for (size_t i = 0; i < maxLearned; i++)
	{
		if (templates[i] && templates[i]->getType() == type)
			return templates[i]->clone();
	}
	return 0;
}

std::ostream& operator<<(std::ostream& os, const MateriaSource& obj)
{
	(void)obj;
	os << "MateriaSource";
	return os;
}
