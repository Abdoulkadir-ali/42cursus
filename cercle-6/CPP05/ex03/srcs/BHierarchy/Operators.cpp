/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:52:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BHierarchy.hpp"

std::ostream &operator<<(std::ostream &out, const BHierarchy &instance)
{
    out << "Instance <" << instance.getName() << "> of class <" << instance.getType() << ">";
    return out;
}
