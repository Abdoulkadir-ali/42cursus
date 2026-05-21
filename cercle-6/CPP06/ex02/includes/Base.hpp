/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:35:07 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:35:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
#define BASE_HPP

#include <cstdlib>
#include <ctime>
#include <iostream>

struct Base
{
    virtual ~Base();
};

struct A : public Base {};
struct B : public Base {};
struct C : public Base {};

Base *generate(void);
void  identify(Base *p);
void  identify(Base &p);

#endif
