/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:50:15 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:50:19 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

int main(void)
{
	// --- Subject example ---
	std::cout << "=== Subject example ===" << std::endl;
	{
		Span sp(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl; // 2
		std::cout << "Longest span:  " << sp.longestSpan()  << std::endl; // 14
	}

	// --- Exception: span full ---
	std::cout << "\n=== Span full exception ===" << std::endl;
	{
		Span sp(3);
		sp.addNumber(1);
		sp.addNumber(2);
		sp.addNumber(3);
		try {
			sp.addNumber(4);
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	// --- Exception: too few elements ---
	std::cout << "\n=== Too few elements exception ===" << std::endl;
	{
		Span sp(5);
		try {
			sp.shortestSpan();
		} catch (std::exception& e) {
			std::cout << "shortestSpan: " << e.what() << std::endl;
		}
		sp.addNumber(42);
		try {
			sp.longestSpan();
		} catch (std::exception& e) {
			std::cout << "longestSpan:  " << e.what() << std::endl;
		}
	}

	// --- Large test: 10,000 numbers ---
	std::cout << "\n=== Large span (10,000 numbers) ===" << std::endl;
	{
		const unsigned int SIZE = 10000;
		Span sp(SIZE);

		std::srand(42);
		std::vector<int> numbers;
		numbers.reserve(SIZE);
		for (unsigned int i = 0; i < SIZE; ++i)
			numbers.push_back(std::rand());

		sp.addRange(numbers.begin(), numbers.end());

		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
		std::cout << "Longest span:  " << sp.longestSpan()  << std::endl;
	}

	// --- Duplicate values (shortest span should be 0) ---
	std::cout << "\n=== Duplicate values ===" << std::endl;
	{
		Span sp(4);
		sp.addNumber(5);
		sp.addNumber(5);
		sp.addNumber(10);
		sp.addNumber(20);
		std::cout << "Shortest span: " << sp.shortestSpan() << std::endl; // 0
		std::cout << "Longest span:  " << sp.longestSpan()  << std::endl; // 15
	}

	return 0;
}
