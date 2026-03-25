/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Creators.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:10:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 11:10:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <string>

static AForm* createShrubbery(const std::string &target) { return new ShrubberyCreationForm(target); }
static AForm* createRobotomy(const std::string &target) { return new RobotomyRequestForm(target); }
static AForm* createPardon(const std::string &target) { return new PresidentialPardonForm(target); }

struct Entry { const char *name; AForm*(*creator)(const std::string&); };

// implement the private static helper on Intern
AForm* Intern::createForm(const std::string &formName, const std::string &target)
{
    static Entry table[] = {
        { "shrubbery creation", &createShrubbery },
        { "robotomy request",   &createRobotomy },
        { "presidential pardon", &createPardon }
    };

    for (size_t i = 0; i < sizeof(table)/sizeof(table[0]); ++i) {
        if (formName == table[i].name)
            return table[i].creator(target);
    }
    return NULL;
}
