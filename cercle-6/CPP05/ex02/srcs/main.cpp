/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 10:16:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int	main(void)
{
	std::cout << "=== Basic Bureaucrat tests ===" << std::endl;
	Bureaucrat kevin("Kevin", "Bureaucrat", 10, 1, 150);

	kevin.demote();
	kevin.promote();

	try { kevin.setGrade(-10); }
	catch (std::exception &e) { std::cerr << "Caught (setGrade -10): " << e.what() << std::endl; }

	try { kevin.setGrade(151); }
	catch (std::exception &e) { std::cerr << "Caught (setGrade 151): " << e.what() << std::endl; }

	try {
		Bureaucrat badRange("BadRange", "Bureaucrat", 10, 150, 1);
	}
	catch (std::exception &e) { std::cerr << "Caught (bad range ctor): " << e.what() << std::endl; }

	std::cout << "=== Boundary promote/demote tests ===" << std::endl;
	try {
		Bureaucrat top("Top", "Bureaucrat", 1, 1, 150);
		top.promote();
	}
	catch (std::exception &e) { std::cerr << "Caught (promote beyond top): " << e.what() << std::endl; }

	try {
		Bureaucrat bottom("Bottom", "Bureaucrat", 150, 1, 150);
		bottom.demote();
	}
	catch (std::exception &e) { std::cerr << "Caught (demote beyond bottom): " << e.what() << std::endl; }

	std::cout << "=== AForm tests ===" << std::endl;
	try {
		ShrubberyCreationForm scf("home");
		Bureaucrat signer("LowSigner", "Bureaucrat", 150, 1, 150);
		// signing should fail for low signer
		scf.beSigned(signer);
	}
	catch (std::exception &e) { std::cerr << "Caught (shrub sign attempt): " << e.what() << std::endl; }

	try {
		RobotomyRequestForm rrf("robot_target");
		Bureaucrat signer2("Signer2", "Bureaucrat", 50, 1, 150);
		signer2.executeForm(rrf); // should fail because not signed
		rrf.beSigned(signer2);
		signer2.executeForm(rrf); // attempt execution (may succeed or fail randomly)
	}
	catch (std::exception &e) { std::cerr << "Caught (robotomy attempt): " << e.what() << std::endl; }

	try {
		PresidentialPardonForm ppf("president_target");
		Bureaucrat exec("Exec", "Bureaucrat", 3, 1, 150);
		ppf.beSigned(exec);
		exec.executeForm(ppf);
	}
	catch (std::exception &e) { std::cerr << "Caught (president attempt): " << e.what() << std::endl; }

	std::cout << "Done !" << std::endl;
	return (0);
}