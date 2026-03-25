/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:30:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

bool Bureaucrat::isValidGrade(int grade) const
{
    return (grade >= this->minGrade && grade <= this->maxGrade);
}

void Bureaucrat::setGrade(int new_grade)
{
    if (new_grade < this->minGrade)
        throw Bureaucrat::GradeTooHighException();
    if (new_grade > this->maxGrade)
        throw Bureaucrat::GradeTooLowException();
    std::cout << "Bureaucrat " << this->name << " grade has changed from " << this->grade << " to " << new_grade << std::endl;
    this->grade = new_grade;
}

void Bureaucrat::demote(void)
{
    if (this->grade + 1 > this->maxGrade)
        throw Bureaucrat::GradeTooLowException();
    this->grade++;
    std::cout << "Bureaucrat " << this->name << " has been demoted. " << this->showCurrentGrade() << std::endl;
}

void Bureaucrat::promote(void)
{
    if (this->grade - 1 < this->minGrade)
        throw Bureaucrat::GradeTooHighException();
    this->grade--;
    std::cout << "Bureaucrat " << this->name << " has been promoted. " << this->showCurrentGrade() << std::endl;
}

void Bureaucrat::validateGradeRange(int minG, int maxG)
{
    if (minG > maxG)
        throw Bureaucrat::InvalidGradeRangeException();
    if (minG < 1 || maxG > 150)
        throw Bureaucrat::InvalidGradeRangeException();
    this->minGrade = minG;
    this->maxGrade = maxG;
}

