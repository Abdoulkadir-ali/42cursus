/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:17 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:15:21 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

const std::string &Bureaucrat::getName(void) const    { return this->name; }
const std::string &Bureaucrat::getType(void) const    { return this->type; }
int Bureaucrat::getGrade(void) const                  { return this->grade; }
int Bureaucrat::getMinGrade(void) const               { return this->minGrade; }
int Bureaucrat::getMaxGrade(void) const               { return this->maxGrade; }
