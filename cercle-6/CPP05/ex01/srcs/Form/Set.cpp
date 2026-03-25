/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:07:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:48:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

bool Form::isValidGrade(int grade) const
{
    return (grade >= this->getMinGrade() && grade <= this->getMaxGrade());
}

void Form::beSigned(Bureaucrat &b)
{
    if (b.getGrade() > this->requiredGradeToSign)
        throw BHierarchy::GradeTooLowException();
    this->isSigned = true;
    std::cout << "Form " << this->getName() << " has been signed by " << b.getName() << std::endl;
}

