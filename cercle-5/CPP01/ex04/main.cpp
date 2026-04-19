/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 00:18:56 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 00:20:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Sed.hpp"

int main(int argc, char **argv)
{
    if (argc == 4)
        replace(argv[1], argv[2], argv[3]);
    else
        std::cerr << "Usage: " << argv[0] << " <filename> <find> <replace>" << std::endl;
    return 0;
}