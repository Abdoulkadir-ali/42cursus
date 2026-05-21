/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Result.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:19:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 23:27:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Result.hpp"

Result::Result()
    : charValue(0), charValid(false),
      intValue(0), intValid(false),
      floatValue(0.0f), floatValid(false),
      doubleValue(0.0), doubleValid(false),
      special(SPECIAL_NONE)
{}

Result::Result(const Parser &parser)
    : charValue(0), charValid(false),
      intValue(0), intValid(false),
      floatValue(0.0f), floatValid(false),
      doubleValue(0.0), doubleValid(false),
      special(SPECIAL_NONE)
{
    char   c  = 0;
    int    i  = 0;
    double d  = 0.0;
    SpecialValue sp = SPECIAL_NONE;

    if (parser.parseChar(c))
        fillChar(c);
    else if (parser.parseInt(i))
        fillInt(i);
    else if (parser.parseDouble(d, sp))
        fillDouble(d, sp);
}

Result::Result(const Result &copy)
    : charValue(copy.charValue), charValid(copy.charValid),
      intValue(copy.intValue), intValid(copy.intValid),
      floatValue(copy.floatValue), floatValid(copy.floatValid),
      doubleValue(copy.doubleValue), doubleValid(copy.doubleValid),
      special(copy.special)
{}

Result &Result::operator=(const Result &copy)
{
    if (this != &copy)
    {
        charValue   = copy.charValue;   charValid   = copy.charValid;
        intValue    = copy.intValue;    intValid    = copy.intValid;
        floatValue  = copy.floatValue;  floatValid  = copy.floatValid;
        doubleValue = copy.doubleValue; doubleValid = copy.doubleValid;
        special     = copy.special;
    }
    return *this;
}

Result::~Result() {}

void Result::fillChar(char c)
{
    charValue   = c;
    charValid   = true;
    intValue    = static_cast<int>(c);
    intValid    = true;
    floatValue  = static_cast<float>(c);
    floatValid  = true;
    doubleValue = static_cast<double>(c);
    doubleValid = true;
}

void Result::fillInt(int i)
{
    intValue    = i;
    intValid    = true;
    floatValue  = static_cast<float>(i);  floatValid  = true;
    doubleValue = static_cast<double>(i); doubleValid = true;
    if (i >= 0 && i <= 127)
        { charValue = static_cast<char>(i); charValid = true; }
}

void Result::fillDouble(double d, SpecialValue sp)
{
    special     = sp;
    doubleValue = d;                      doubleValid = true;
    floatValue  = static_cast<float>(d);  floatValid  = true;
    if (sp != SPECIAL_NONE)
        return;
    if (d >= static_cast<double>(std::numeric_limits<int>::min()) &&
        d <= static_cast<double>(std::numeric_limits<int>::max()) &&
        std::floor(d) == d)
        { intValue = static_cast<int>(d); intValid = true; }
    if (d >= 0.0 && d <= 127.0 && std::floor(d) == d)
        { charValue = static_cast<char>(d); charValid = true; }
}

static void printFloat(std::ostream &os, double value, bool appendF)
{
    std::ios::fmtflags oldFlags = os.flags();
    std::streamsize    oldPrec  = os.precision();
    os << std::fixed << std::setprecision(1) << value;
    if (appendF) os << 'f';
    os.flags(oldFlags);
    os.precision(oldPrec);
}

std::ostream &operator<<(std::ostream &os, const Result &r)
{
    os << "char: ";
    if (!r.charValid)
        os << "impossible";
    else if (!std::isprint(static_cast<unsigned char>(r.charValue)))
        os << "Non displayable";
    else
        os << '\'' << r.charValue << '\'';

    os << "\nint: ";
    if (!r.intValid)
        os << "impossible";
    else
        os << r.intValue;

    os << "\nfloat: ";
    if (!r.floatValid)
        os << "impossible";
    else if (r.special == SPECIAL_NAN)
        os << "nanf";
    else if (r.special == SPECIAL_POS_INF)
        os << "+inff";
    else if (r.special == SPECIAL_NEG_INF)
        os << "-inff";
    else
        printFloat(os, r.floatValue, true);

    os << "\ndouble: ";
    if (!r.doubleValid)
        os << "impossible";
    else if (r.special == SPECIAL_NAN)
        os << "nan";
    else if (r.special == SPECIAL_POS_INF)
        os << "+inf";
    else if (r.special == SPECIAL_NEG_INF)
        os << "-inf";
    else
        printFloat(os, r.doubleValue, false);
    os << '\n';
    return os;
}
