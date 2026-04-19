/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:54:21 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 12:56:25 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

int main(void)
{
    int N = 5;
    Zombie *horde = zombieHorde(N, "kadir");

    for (size_t i = 0; i < N; i++)
        horde[i].announce();
    delete[] horde;
    return (0);
}