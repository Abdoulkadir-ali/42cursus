/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Result.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:17:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:23:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESULT_HPP
#define RESULT_HPP

#include <iostream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <limits>
#include "Parser.hpp"

class Result
{
    private:
        void fillChar(char c);
        void fillInt(int i);
        void fillDouble(double d, SpecialValue sp);

    public:
        char         charValue;
        bool         charValid;
        int          intValue;
        bool         intValid;
        float        floatValue;
        bool         floatValid;
        double       doubleValue;
        bool         doubleValid;
        SpecialValue special;

        Result();
        Result(const Parser &parser);
        Result(const Result &copy);
        Result &operator=(const Result &copy);
        ~Result();
};

std::ostream &operator<<(std::ostream &os, const Result &r);

#endif
