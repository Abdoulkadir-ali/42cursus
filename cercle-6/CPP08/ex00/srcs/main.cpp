/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:48:36 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:50:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main(void)
{
	// Test with std::vector
	{
		std::vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.push_back(3);
		v.push_back(4);
		v.push_back(5);

		std::cout << "=== std::vector ===" << std::endl;
		try {
			std::vector<int>::const_iterator it = easyfind(v, 3);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}

		try {
			std::vector<int>::const_iterator it = easyfind(v, 99);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	// Test with std::list
	{
		std::list<int> l;
		l.push_back(10);
		l.push_back(20);
		l.push_back(30);

		std::cout << "\n=== std::list ===" << std::endl;
		try {
			std::list<int>::const_iterator it = easyfind(l, 20);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}

		try {
			std::list<int>::const_iterator it = easyfind(l, 42);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	// Test with std::deque
	{
		std::deque<int> d;
		d.push_back(100);
		d.push_back(200);
		d.push_back(300);

		std::cout << "\n=== std::deque ===" << std::endl;
		try {
			std::deque<int>::const_iterator it = easyfind(d, 100);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}

		try {
			std::deque<int>::const_iterator it = easyfind(d, 0);
			std::cout << "Found: " << *it << std::endl;
		} catch (std::exception& e) {
			std::cout << "Exception: " << e.what() << std::endl;
		}
	}

	return 0;
}
