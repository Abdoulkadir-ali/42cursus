/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Show.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:27:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

std::string Bureaucrat::showGradeRange(void) const
{
    std::stringstream ss;
    ss << "Minimum grade: " << this->minGrade << ", Maximum grade: " << this->maxGrade;
    return ss.str();
}

std::string Bureaucrat::showCurrentGrade(void) const
{
    std::stringstream ss;
    ss << "Current grade: " << this->grade;
    return ss.str();
}

void Bureaucrat::showAttributes(void) const
{
    std::cout << "Showing attributes of : " << *this << std::endl;
    std::cout << "Type: " << this->type << std::endl;
    std::cout << "Name: " << this->name << std::endl;
    std::cout << "Grade: " << this->grade << std::endl << std::endl;
}