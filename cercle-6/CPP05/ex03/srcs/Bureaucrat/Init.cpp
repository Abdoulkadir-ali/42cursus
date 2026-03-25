/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:44:12 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
	: BHierarchy("Username", "Type", 1, 150), grade(150)
{
	std::cout << "Bureaucrat " << this->getName() << " has been constructed from scratch" << std::endl;
	this->showAttributes();
}

Bureaucrat::Bureaucrat(const std::string &name, const std::string &type, int grade, int minGrade, int maxGrade)
	: BHierarchy(name, type, minGrade, maxGrade), grade(grade)
{
	std::cout << "Bureaucrat " << this->getName() << " constructed (grade=" << this->grade << ")" << std::endl;
	this->showAttributes();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: BHierarchy(other.getName(), other.getType(), other.getMinGrade(), other.getMaxGrade()), grade(other.grade)
{
	std::cout << "Bureaucrat " << this->getName() << " has been constructed by copy" << std::endl;
	this->showAttributes();
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat " << this->getName() << " has been destructed" << std::endl;
}

