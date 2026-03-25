/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:37:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:37:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>

void RobotomyRequestForm::executeAction(void) const
{
    std::cout << "Drilling noises... bzzzzzzz..." << std::endl;
    int r = std::rand() % 2;
    if (r == 0)
        std::cout << this->getName() << " has been robotomized successfully" << std::endl;
    else
        std::cout << this->getName() << " robotomy failed" << std::endl;
}
