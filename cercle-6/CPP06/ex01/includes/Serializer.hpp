/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:32:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:32:46 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <stdint.h>
#include "Data.hpp"

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer &copy);
        Serializer &operator=(const Serializer &copy);
        ~Serializer();

    public:
        static uintptr_t serialize(Data *ptr);
        static Data      *deserialize(uintptr_t raw);
};

#endif
