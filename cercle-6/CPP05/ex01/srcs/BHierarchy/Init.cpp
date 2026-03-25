/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:52:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BHierarchy.hpp"

BHierarchy::BHierarchy()
    : name("Unnamed"), type("BHierarchy"), minGrade(1), maxGrade(150)
{
}

BHierarchy::BHierarchy(const std::string &name, const std::string &type, int minG, int maxG)
    : name(name), type(type), minGrade(1), maxGrade(150)
{
    this->validateGradeRange(minG, maxG);
}

BHierarchy::~BHierarchy() {}
