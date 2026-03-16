/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 03:57:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 06:29:54 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"

int main(void)
{
    Animal animals[100];
    int i;

    i = 0;
    while (i < 50)
        animals[i++] = Cat();
    while (i < 100)
        animals[i++] = Dog();
    return (0);
}