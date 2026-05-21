/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:17:38 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:23:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <cerrno>
#include <cstdlib>
#include <cctype>
#include <limits>

enum SpecialValue
{
    SPECIAL_NONE,
    SPECIAL_NAN,
    SPECIAL_POS_INF,
    SPECIAL_NEG_INF
};

class Parser
{
    private:
        std::string string;

        bool isSpecial(SpecialValue &sp, double &value) const;
        bool parseNumeric(double &value) const;

    public:
        Parser();
        Parser(const std::string &input);
        Parser(const Parser &copy);
        Parser &operator=(const Parser &copy);
        ~Parser();

        bool parseChar(char &value) const;
        bool parseInt(int &value) const;
        bool parseDouble(double &value, SpecialValue &sp) const;
};

#endif
