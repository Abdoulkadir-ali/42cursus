/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Show.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:08:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:00:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

std::string Form::showCurrentGrade(void) const
{
    std::stringstream ss;
    ss << "Required grade to sign: " << this->requiredGradeToSign << ", to execute: " << this->requiredGradeToExecute;
    return ss.str();
}

std::string Form::showRequiredGrade(void) const
{
    return this->showCurrentGrade();
}

void Form::showAttributes(void) const
{
    BHierarchy::showAttributes();
    std::cout << "Signed: " << (this->isSigned ? "yes" : "no") << std::endl;
    std::cout << this->showCurrentGrade() << std::endl << std::endl;
}
