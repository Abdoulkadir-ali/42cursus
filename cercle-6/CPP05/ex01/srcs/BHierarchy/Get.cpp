/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Get.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:52:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BHierarchy.hpp"

const std::string &BHierarchy::getName(void) const { return this->name; }
const std::string &BHierarchy::getType(void) const { return this->type; }
int BHierarchy::getMinGrade(void) const { return this->minGrade; }
int BHierarchy::getMaxGrade(void) const { return this->maxGrade; }
