/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 11:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern::~Intern() {}
Intern& Intern::operator=(const Intern&) { return *this; }

AForm* Intern::makeForm(const std::string &formName, const std::string &target) const
{
    AForm *f = Intern::createForm(formName, target);
    if (f)
        std::cout << "Intern creates " << formName << std::endl;
    else
        std::cerr << "Intern: unknown form '" << formName << "'" << std::endl;
    return f;
}
