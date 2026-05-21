/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 23:30:59 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 23:31:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Array.hpp"

int main(void)
{
	Array<int> empty;
	std::cout << "empty.size() = " << empty.size() << std::endl;

	Array<int> ints(5);
	std::cout << "ints.size() = " << ints.size() << std::endl;
	for (unsigned int i = 0; i < ints.size(); i++)
		ints[i] = static_cast<int>(i * 10);

	Array<int> copy(ints);
	copy[0] = 999;
	std::cout << "ints[0] after modifying copy: " << ints[0] << std::endl;
	std::cout << "copy[0]: " << copy[0] << std::endl;

	Array<int> assigned;
	assigned = ints;
	ints[1] = 888;
	std::cout << "ints[1] after modifying original: " << ints[1] << std::endl;
	std::cout << "assigned[1]: " << assigned[1] << std::endl;

	try
	{
		std::cout << ints[100] << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	Array<std::string> strs(3);
	strs[0] = "hello";
	strs[1] = "world";
	strs[2] = "42";
	for (unsigned int i = 0; i < strs.size(); i++)
		std::cout << "strs[" << i << "] = " << strs[i] << std::endl;

	return 0;
}
