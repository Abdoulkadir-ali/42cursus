/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:52:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BHierarchy.hpp"

const char* BHierarchy::InvalidGradeRangeException::what() const throw()
{
    return "Invalid grade range (min must be >=1, max <=150 and min <= max)";
}

const char* BHierarchy::GradeTooHighException::what() const throw()
{
    return "Grade is too high (above minimum)";
}

const char* BHierarchy::GradeTooLowException::what() const throw()
{
    return "Grade is too low (below maximum)";
}
