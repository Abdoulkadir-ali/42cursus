/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:50:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/06/08 15:44:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char* argv[]) 
{
    if (argc != 2) 
{
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    BitcoinExchange btc;
    try {
        btc.loadDatabase("data.csv");
    } catch (const std::exception& e) 
{
        std::cerr << e.what() << std::endl;
        return 1;
    }

    btc.processInput(argv[1]);
    return 0;
}

