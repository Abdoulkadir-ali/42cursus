/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:59:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BHierarchy.hpp"

void BHierarchy::validateGradeRange(int minG, int maxG)
{
    if (minG > maxG)
        throw BHierarchy::InvalidGradeRangeException();
    if (minG < this->minGrade || maxG > this->maxGrade)
        throw BHierarchy::InvalidGradeRangeException();
    this->minGrade = minG;
    this->maxGrade = maxG;
}
