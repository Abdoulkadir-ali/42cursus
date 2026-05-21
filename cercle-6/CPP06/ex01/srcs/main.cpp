/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:32:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:32:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Serializer.hpp"
#include <iostream>

int main(void)
{
    Data original;
    original.id    = 42;
    original.label = "hello";
    original.value = 3.14;

    std::cout << "Original pointer : " << &original << std::endl;
    std::cout << "  id    = " << original.id    << std::endl;
    std::cout << "  label = " << original.label << std::endl;
    std::cout << "  value = " << original.value << std::endl;

    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "\nSerialized (raw) : " << raw << std::endl;

    Data *restored = Serializer::deserialize(raw);
    std::cout << "\nRestored pointer : " << restored << std::endl;
    std::cout << "  id    = " << restored->id    << std::endl;
    std::cout << "  label = " << restored->label << std::endl;
    std::cout << "  value = " << restored->value << std::endl;

    std::cout << "\nPointers match   : "
              << (restored == &original ? "YES" : "NO") << std::endl;

    return 0;
}
