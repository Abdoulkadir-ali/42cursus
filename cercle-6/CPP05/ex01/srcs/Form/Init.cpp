/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:05:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:05:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"
#include "Bureaucrat.hpp"

Form::Form()
	: BHierarchy("UnnamedForm", "Form", 1, 150), isSigned(false), requiredGradeToSign(150), requiredGradeToExecute(150)
{
	std::cout << "<" << this->type << "> "  << this->getName() << " has been constructed from scratch" << std::endl;
	this->showAttributes();
}

Form::Form(const std::string &name, const std::string &type, int grade, int minGrade, int maxGrade)
	: BHierarchy(name, type, minGrade, maxGrade), isSigned(false), requiredGradeToSign(grade), requiredGradeToExecute(grade)
{
	// validate required grades against the hierarchy limits
	if (!this->isValidGrade(grade)) {
		if (grade < this->getMinGrade())
			throw BHierarchy::GradeTooHighException();
		else
			throw BHierarchy::GradeTooLowException();
	}
	this->showAttributes();
}

Form::Form(const Form &other)
	: BHierarchy(other.getName(), other.getType(), other.getMinGrade(), other.getMaxGrade()), isSigned(other.isSigned), requiredGradeToSign(other.requiredGradeToSign), requiredGradeToExecute(other.requiredGradeToExecute)
{
}

Form::~Form()
{}

