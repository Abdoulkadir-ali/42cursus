/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/11 03:14:12 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 04:23:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>

class Fixed
{
    private:
	    int                 value;
        static const int    bits = 8;
            
    public:
        Fixed();
        Fixed(const Fixed &c);
        Fixed &operator=(const Fixed &c);
        ~Fixed();
        int getRawBits(void) const;
        void setRawBits(int const raw);
};