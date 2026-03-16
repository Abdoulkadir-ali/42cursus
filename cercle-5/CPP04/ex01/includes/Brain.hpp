/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 04:36:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/13 06:26:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <iostream>

class Brain
{
    private:
        std::string type;
        std::string ideas[100];
    public:
        Brain(void);
        Brain(const Brain &brain);
        ~Brain();
};