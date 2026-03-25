/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Show.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:58:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BHierarchy.hpp"

std::string BHierarchy::showGradeRange(void) const
{
    std::stringstream ss;
    ss << "Minimum grade: " << this->minGrade << ", Maximum grade: " << this->maxGrade;
    return ss.str();
}

void BHierarchy::showAttributes(void) const
{
    std::cout << "Showing attributes of : " << *this << std::endl;
    std::cout << "Type: " << this->getType() << std::endl;
    std::cout << "Name: " << this->getName() << std::endl;
    std::cout << this->showGradeRange() << std::endl << std::endl;
}
