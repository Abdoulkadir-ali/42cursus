/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 03:57:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 13:38:28 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"

int main(void)
{
	const int SIZE = 10;
	Animal *animals[SIZE];

	for (size_t i = 0; i < SIZE / 2; i++)
		animals[i] = new Cat();

	for (size_t i = SIZE / 2; i < SIZE; i++)
		animals[i] = new Dog();

	std::cout << "\n--- Sounds ---" << std::endl;
	for (size_t i = 0; i < SIZE; i++)
		animals[i]->makeSound();

	std::cout << "\n--- Delete all via Animal* (virtual destructor required!) ---" << std::endl;
	for (size_t i = 0; i < SIZE; i++)
		delete animals[i];

	return 0;
}
