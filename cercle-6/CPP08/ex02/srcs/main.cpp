/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:51:20 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:52:35 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MutantStack.hpp"

// Helper to print a separator
static void printSection(const std::string& title)
{
	std::cout << "\n=== " << title << " ===" << std::endl;
}

int main(void)
{
	// --- Subject example with MutantStack ---
	printSection("Subject example - MutantStack<int>");
	{
		MutantStack<int> mstack;
		mstack.push(5);
		mstack.push(17);
		std::cout << mstack.top() << std::endl;  // 17
		mstack.pop();
		std::cout << mstack.size() << std::endl; // 1
		mstack.push(3);
		mstack.push(5);
		mstack.push(737);
		mstack.push(0);

		MutantStack<int>::iterator it  = mstack.begin();
		MutantStack<int>::iterator ite = mstack.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
		std::stack<int> s(mstack); // copy to plain std::stack compiles fine
	}

	// --- Same output with std::list ---
	printSection("Same test - std::list<int>");
	{
		std::list<int> lst;
		lst.push_back(5);
		lst.push_back(17);
		std::cout << lst.back() << std::endl;  // 17
		lst.pop_back();
		std::cout << lst.size() << std::endl;  // 1
		lst.push_back(3);
		lst.push_back(5);
		lst.push_back(737);
		lst.push_back(0);

		std::list<int>::iterator it  = lst.begin();
		std::list<int>::iterator ite = lst.end();
		++it;
		--it;
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}

	// --- Reverse iterators ---
	printSection("Reverse iteration");
	{
		MutantStack<int> mstack;
		mstack.push(1);
		mstack.push(2);
		mstack.push(3);

		MutantStack<int>::reverse_iterator rit  = mstack.rbegin();
		MutantStack<int>::reverse_iterator rite = mstack.rend();
		while (rit != rite)
		{
			std::cout << *rit << std::endl; // 3 2 1
			++rit;
		}
	}

	// --- Const iterators ---
	printSection("Const iteration");
	{
		MutantStack<int> mstack;
		mstack.push(10);
		mstack.push(20);
		mstack.push(30);

		const MutantStack<int>& cmstack = mstack;
		MutantStack<int>::const_iterator cit  = cmstack.begin();
		MutantStack<int>::const_iterator cite = cmstack.end();
		while (cit != cite)
		{
			std::cout << *cit << std::endl; // 10 20 30
			++cit;
		}
	}

	// --- MutantStack with std::string ---
	printSection("MutantStack<std::string>");
	{
		MutantStack<std::string> sstack;
		sstack.push("hello");
		sstack.push("world");
		sstack.push("42");

		MutantStack<std::string>::iterator it  = sstack.begin();
		MutantStack<std::string>::iterator ite = sstack.end();
		while (it != ite)
		{
			std::cout << *it << std::endl;
			++it;
		}
	}
	return 0;
}
