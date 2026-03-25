/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operators.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 09:46:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Form.hpp"

std::ostream &operator<<(std::ostream &out, const Form &instance)
{
    out << "Instance <" << instance.getName() << "> of class <" << instance.getType() << ">";
    return out;
}
