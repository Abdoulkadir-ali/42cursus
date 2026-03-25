/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:06:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:09:38 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

const std::string &AForm::getName(void) const { return BHierarchy::getName(); }
const std::string &AForm::getType(void) const { return BHierarchy::getType(); }
int AForm::getGrade(void) const { return this->requiredGradeToSign; }
int AForm::getMinGrade(void) const { return BHierarchy::getMinGrade(); }
int AForm::getMaxGrade(void) const { return BHierarchy::getMaxGrade(); }