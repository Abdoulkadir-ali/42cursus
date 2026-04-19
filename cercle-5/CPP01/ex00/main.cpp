/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:54:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 00:52:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    // Heap allocation: zombie lives beyond the function call
    Zombie *heapZombie = newZombie("HeapBob");
    heapZombie->announce();

    // Stack allocation: zombie is created and destroyed inside randomChump
    randomChump("StackAlice");

    // Heap zombie must be deleted manually
    delete heapZombie;
    return (0);
}