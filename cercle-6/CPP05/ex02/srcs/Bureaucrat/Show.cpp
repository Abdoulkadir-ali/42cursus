/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Show.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 10:00:05 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

std::string Bureaucrat::showCurrentGrade(void) const
{
    std::stringstream ss;
    ss << "Current grade: " << this->grade;
    return ss.str();
}

void Bureaucrat::showAttributes(void) const
{
    BHierarchy::showAttributes();
    std::cout << "Grade: " << this->grade << std::endl << std::endl;
}