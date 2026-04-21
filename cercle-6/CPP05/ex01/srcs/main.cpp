/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 20:20:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

int	main(void)
{
	std::cout << "=== Basic Bureaucrat tests ===" << std::endl;
	Bureaucrat kevin("Kevin", "Bureaucrat", 10, 1, 150);

	kevin.demote();
	kevin.promote();

	try { kevin.setGrade(-10);}
	catch (std::exception &e) { std::cerr << "Caught (setGrade -10): " << e.what() << std::endl; }

	try { kevin.setGrade(151); }
	catch (std::exception &e) { std::cerr << "Caught (setGrade 151): " << e.what() << std::endl; }

	try { Bureaucrat badRange("BadRange", "Bureaucrat", 10, 150, 1);}
	catch (std::exception &e) { std::cerr << "Caught (bad range ctor): " << e.what() << std::endl; }
	std::cout << "=== Boundary promote/demote tests ===" << std::endl;
	try
	{
		Bureaucrat top("Top", "Bureaucrat", 1, 1, 150);
		top.promote();
	}
	catch (std::exception &e) { std::cerr << "Caught (promote beyond top): " << e.what() << std::endl; }
	try
	{
		Bureaucrat bottom("Bottom", "Bureaucrat", 150, 1, 150);
		bottom.demote();
	}
	catch (std::exception &e) { std::cerr << "Caught (demote beyond bottom): " << e.what() << std::endl; }
	std::cout << "=== Form tests ===" << std::endl;
	try {
		Form f1("TaxForm", "Form", 50, 1, 150);
		Bureaucrat signer("LowSigner", "Bureaucrat", 100, 1, 150);
		f1.beSigned(signer);
	}
	catch (std::exception &e) { std::cerr << "Caught (form sign attempt): " << e.what() << std::endl; }

	try {
		Form badForm("BadForm", "Form", 0, 1, 150);
	}
	catch (std::exception &e) { std::cerr << "Caught (bad form ctor): " << e.what() << std::endl; }

	std::cout << "Done !" << std::endl;
	return (0);
}