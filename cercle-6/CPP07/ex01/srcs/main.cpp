/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 23:30:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 23:30:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Iter.hpp"

int main(void)
{
	int	ints[] = {1, 2, 3, 4, 5};
	std::cout << "=== int array (print) ===" << std::endl;
	::iter(ints, 5, print<int>);

	std::cout << "=== int array (increment then print) ===" << std::endl;
	::iter(ints, 5, increment<int>);
	::iter(ints, 5, print<int>);

	std::string strs[] = {"hello", "world", "42"};
	std::cout << "=== string array (print) ===" << std::endl;
	::iter(strs, 3, print<std::string>);

	const double doubles[] = {1.1, 2.2, 3.3};
	std::cout << "=== const double array (print) ===" << std::endl;
	::iter(doubles, 3, print<double>);

	return 0;
}
