/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:18:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:27:40 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser() : string() {}

Parser::Parser(const std::string &input) : string(input) {}

Parser::Parser(const Parser &copy) : string(copy.string) {}

Parser &Parser::operator=(const Parser &copy)
{
    if (this != &copy)
        string = copy.string;
    return *this;
}

Parser::~Parser() {}

bool Parser::parseChar(char &value) const
{
    if (string.size() == 1 && !std::isdigit(static_cast<unsigned char>(string[0])))
    {
        value = string[0];
        return true;
    }
    if (string.size() == 3 && string[0] == '\'' && string[2] == '\'')
    {
        value = string[1];
        return true;
    }
    return false;
}

bool Parser::parseInt(int &value) const
{
    char *end = 0;
    errno = 0;

    long parsed = std::strtol(string.c_str(), &end, 10);
    if (end == string.c_str() || *end != '\0' || errno == ERANGE)
        return false;
    if (parsed < std::numeric_limits<int>::min() || parsed > std::numeric_limits<int>::max())
        return false;
    value = static_cast<int>(parsed);
    return true;
}

bool Parser::isSpecial(SpecialValue &sp, double &value) const
{
    if (string == "nan"  || string == "nanf")
        { sp = SPECIAL_NAN;     value = std::numeric_limits<double>::quiet_NaN();  return true; }
    if (string == "inf"  || string == "inff" || string == "+inf" || string == "+inff")
        { sp = SPECIAL_POS_INF; value = std::numeric_limits<double>::infinity();   return true; }
    if (string == "-inf" || string == "-inff")
        { sp = SPECIAL_NEG_INF; value = -std::numeric_limits<double>::infinity();  return true; }
    return false;
}

bool Parser::parseNumeric(double &value) const
{
    std::string s = string;
    if (!s.empty() && s[s.size() - 1] == 'f')
        s.erase(s.size() - 1);
    if (s.empty())
        return false;

    char *end = 0;
    errno = 0;
    value = std::strtod(s.c_str(), &end);
    return !(end == s.c_str() || *end != '\0' || errno == ERANGE);
}

bool Parser::parseDouble(double &value, SpecialValue &sp) const
{
    sp = SPECIAL_NONE;
    if (isSpecial(sp, value))
        return true;
    return parseNumeric(value);
}
