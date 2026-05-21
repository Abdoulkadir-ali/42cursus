/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:18:25 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 23:27:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScalarConverter.hpp"
#include <iostream>
#include <string>

static void debug_main(void)
{
    const std::string cases[] = {
        "a", "Z", " ", "'c'",
        "0", "42", "-42",
        "2147483647",
        "-2147483648",
        "2147483648",
        "0.0f", "4.2f", "-4.2f",
        "42.0f",
        "1.17549e-38f",
        "3.40282e+38f",
        "0.0", "4.2", "-4.2",
        "1.7976931348623157e+308",
        "nan", "nanf",
        "+inf", "+inff",
        "-inf", "-inff",
        "inf", "inff",
        "hello", "42abc", "--1", "1.2.3", ""
    };

    const std::size_t count = sizeof(cases) / sizeof(cases[0]);
    for (std::size_t i = 0; i < count; ++i)
    {
        std::cout << "\033[1;36m[\"" << cases[i] << "\"]\033[0m" << std::endl;
        ScalarConverter::convert(cases[i]);
        std::cout << std::endl;
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        debug_main();
        return 0;
    }
    for (int i = 1; i < argc; ++i)
    {
        if (argc > 2)
            std::cout << "\033[1;36m[\"" << argv[i] << "\"]\033[0m" << std::endl;
        ScalarConverter::convert(argv[i]);
        if (argc > 2)
            std::cout << std::endl;
    }
    return 0;
}

