/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:51:23 by abdoali           #+#    #+#             */
/*   Updated: 2026/06/08 15:44:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
{
        std::cerr << "Error" << std::endl;
        return 1;
    }

    RPN rpn;
    try {
        rpn.evaluate(argv[1]);
    } catch (const std::exception& e) 
{
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}

