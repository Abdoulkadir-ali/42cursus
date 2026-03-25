/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:34:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"


const char* Bureaucrat::GradeTooHighException::what() const throw()
{
	return "Grade is too high (above minimum)";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
	return "Grade is too low (below maximum)";
}

const char* Bureaucrat::InvalidGradeRangeException::what() const throw()
{
	return "Invalid grade range (min must be >=1, max <=150 and min <= max)";
}
