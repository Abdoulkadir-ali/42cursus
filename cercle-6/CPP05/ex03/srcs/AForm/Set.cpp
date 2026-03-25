/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:07:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:09:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

bool AForm::isValidGrade(int grade) const
{
    return (grade >= this->getMinGrade() && grade <= this->getMaxGrade());
}

void AForm::beSigned(Bureaucrat &b)
{
    if (b.getGrade() > this->requiredGradeToSign)
        throw BHierarchy::GradeTooLowException();
    this->isSigned = true;
    std::cout << "AForm " << this->getName() << " has been signed by " << b.getName() << std::endl;
}

