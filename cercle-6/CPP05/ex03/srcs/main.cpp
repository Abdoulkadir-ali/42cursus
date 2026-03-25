/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 10:37:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

int main()
{
	std::cout << "=== Intern-focused tests ===" << std::endl;
	Intern intern;

	// Creation
	AForm *f_shrub = intern.makeForm("shrubbery creation", "home");
	AForm *f_robot = intern.makeForm("robotomy request", "Bender");
	AForm *f_pardon = intern.makeForm("presidential pardon", "Trillian");
	AForm *f_unknown = intern.makeForm("this does not exist", "Nobody");

	// Verify pointers
	std::cout << "Created: " << (f_shrub ? "shrubbery" : "null")
			  << ", " << (f_robot ? "robotomy" : "null")
			  << ", " << (f_pardon ? "pardon" : "null")
			  << ", unknown->" << (f_unknown ? "created" : "null") << std::endl;

	Bureaucrat senior("Senior", "Bureaucrat", 1, 1, 150);
	Bureaucrat junior("Junior", "Bureaucrat", 150, 1, 150);

	// Attempt execute without signing
	if (f_robot) {
		try { senior.executeForm(*f_robot); }
		catch (std::exception &e) { std::cerr << "execute without sign: " << e.what() << std::endl; }
	}

	// Signing with insufficient grade
	if (f_shrub) {
		try { f_shrub->beSigned(junior); }
		catch (std::exception &e) { std::cerr << "sign shrub with junior: " << e.what() << std::endl; }
	}

	// Proper sign + execute
	if (f_shrub) {
		try { f_shrub->beSigned(senior); senior.executeForm(*f_shrub); }
		catch (std::exception &e) { std::cerr << "shrub sign/exec error: " << e.what() << std::endl; }
	}

	if (f_robot) {
		try { f_robot->beSigned(senior); senior.executeForm(*f_robot); }
		catch (std::exception &e) { std::cerr << "robot sign/exec error: " << e.what() << std::endl; }
	}

	if (f_pardon) {
		try { f_pardon->beSigned(senior); senior.executeForm(*f_pardon); }
		catch (std::exception &e) { std::cerr << "pardon sign/exec error: " << e.what() << std::endl; }
	}

	delete f_shrub; delete f_robot; delete f_pardon; delete f_unknown;

	std::cout << "Intern tests completed." << std::endl;
	return 0;
}