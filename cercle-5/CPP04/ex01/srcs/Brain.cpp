/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:36:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 06:15:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain()
    :type("Brain")
{
    std::cout << "Building " <<this->type << std::endl;
}

Brain::Brain(const Brain& copyBrain)
{
    this->type = copyBrain.type;
}

Brain::~Brain()
{
    std::cout << "Killing " << this->type << std::endl;
}