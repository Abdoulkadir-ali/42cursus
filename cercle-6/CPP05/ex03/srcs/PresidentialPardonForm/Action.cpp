/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:38:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:38:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PresidentialPardonForm.hpp"
#include <iostream>

void PresidentialPardonForm::executeAction(void) const
{
    std::cout << this->getName() << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
