/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:35:02 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:35:03 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Base.hpp"

Base::~Base() {}

Base *generate(void)
{
    switch (std::rand() % 3)
    {
        case 0: return new A();
        case 1: return new B();
        default: return new C();
    }
}

void identify(Base *p)
{
    if (dynamic_cast<A *>(p))
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B *>(p))
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C *>(p))
        std::cout << "C" << std::endl;
}

void identify(Base &p)
{
    try { (void)dynamic_cast<A &>(p); std::cout << "A" << std::endl; return; }
    catch (...) {}
    try { (void)dynamic_cast<B &>(p); std::cout << "B" << std::endl; return; }
    catch (...) {}
    try { (void)dynamic_cast<C &>(p); std::cout << "C" << std::endl; return; }
    catch (...) {}
}
