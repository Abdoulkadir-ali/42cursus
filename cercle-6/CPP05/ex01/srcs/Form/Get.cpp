/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:06:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:46:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

const std::string &Form::getName(void) const { return BHierarchy::getName(); }
const std::string &Form::getType(void) const { return BHierarchy::getType(); }
int Form::getGrade(void) const { return this->requiredGradeToSign; }
int Form::getMinGrade(void) const { return BHierarchy::getMinGrade(); }
int Form::getMaxGrade(void) const { return BHierarchy::getMaxGrade(); }