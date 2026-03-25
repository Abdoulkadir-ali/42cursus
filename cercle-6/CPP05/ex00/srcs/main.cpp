/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:48:58 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:32:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int	main(void)
{
	Bureaucrat Kevin("Kevin", "Bureaucrat", 10, 1, 150);

	Kevin.demote();
	Kevin.promote();
	try
	{
        Kevin.setGrade(-10);
		Kevin.setGrade(151);
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
    try
    {
        Bureaucrat Kevin("Kevin", "Bureaucrat", 10, 150, 1);
    }
    catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
    std::cout << "Done !" << std::endl;
	return (0);
}