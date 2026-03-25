/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:05:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:26:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"
#include "Bureaucrat.hpp"

AForm::AForm()
	: BHierarchy("UnnamedAForm", "AForm", 1, 150), isSigned(false), requiredGradeToSign(150), requiredGradeToExecute(150)
{
	std::cout << "<" << this->type << "> "  << this->getName() << " has been constructed from scratch" << std::endl;
	this->showAttributes();
}

AForm::AForm(const std::string &name, const std::string &type, int signGrade, int execGrade, int minGrade, int maxGrade)
	: BHierarchy(name, type, minGrade, maxGrade), isSigned(false), requiredGradeToSign(signGrade), requiredGradeToExecute(execGrade)
{
	// validate required grades against the hierarchy limits
	if (!this->isValidGrade(signGrade)) {
		if (signGrade < this->getMinGrade())
			throw BHierarchy::GradeTooHighException();
		else
			throw BHierarchy::GradeTooLowException();
	}
	if (!this->isValidGrade(execGrade)) {
		if (execGrade < this->getMinGrade())
			throw BHierarchy::GradeTooHighException();
		else
			throw BHierarchy::GradeTooLowException();
	}
	this->showAttributes();
}

AForm::AForm(const AForm &other)
	: BHierarchy(other.getName(), other.getType(), other.getMinGrade(), other.getMaxGrade()), isSigned(other.isSigned), requiredGradeToSign(other.requiredGradeToSign), requiredGradeToExecute(other.requiredGradeToExecute)
{
}

AForm::~AForm()
{}

