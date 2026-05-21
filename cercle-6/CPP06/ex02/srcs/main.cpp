/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:34:47 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:35:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(0)));

    for (int i = 0; i < 9; ++i)
    {
        Base *obj = generate();

        std::cout << "pointer : ";
        identify(obj);

        std::cout << "reference: ";
        identify(*obj);

        std::cout << std::endl;
        delete obj;
    }
    return 0;
}
