/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 20:14:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat()
	: name("Username"), type("Type"), grade(150), minGrade(1), maxGrade(150)
{
    this->validateGradeRange(minGrade, maxGrade);
	std::cout << "Bureaucrat " << this->name << " has been constructed from scratch" << std::endl;
	this->showAttributes();
}

Bureaucrat::Bureaucrat(const std::string &name, const std::string &type, int grade, int minGrade, int maxGrade)
	: name(name), type(type), grade(grade), minGrade(minGrade), maxGrade(maxGrade)	
{
	this->validateGradeRange(minGrade, maxGrade);
	std::cout << "Bureaucrat " << this->name << " constructed (grade=" << this->grade << ")" << std::endl;
	this->showAttributes();
}

Bureaucrat::Bureaucrat(const Bureaucrat &other)
	: name(other.name), type(other.type), grade(other.grade), minGrade(other.minGrade), maxGrade(other.maxGrade)
{
	std::cout << "Bureaucrat " << this->name << " has been constructed by copy" << std::endl;
    this->validateGradeRange(minGrade, maxGrade);
    this->showAttributes();
}

Bureaucrat::~Bureaucrat()
{
	std::cout << "Bureaucrat " << this->name << " has been destructed" << std::endl;
}

