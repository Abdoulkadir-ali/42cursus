/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 03:57:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 07:06:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"

int main(void)
{
    Cat cats[50];
    Dog dogs[50];
    Animal *animals[100];
    int i;

    i = 0;
    while (i < 50)
    {
        cats[i] = Cat();
        dogs[i] = Dog();
        animals[i] = &cats[i];
        animals[i + 50] = &dogs[i];
        i++;
    }
    // Animal test = new Animal(); //This should tell you can't instantiate an object of type Animal because it's abstract
    (void)animals;
    i = 0;
    while (i < 100)
    {
        animals[i]->makeSound();
        std::cout << *animals[i] << std::endl;
        i++;
    }
    return (0);
}