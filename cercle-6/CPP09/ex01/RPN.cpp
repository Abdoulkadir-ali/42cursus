/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:51:18 by abdoali           #+#    #+#             */
/*   Updated: 2026/06/08 15:44:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <cctype>

// ─── Canonical form ───────────────────────────────────────────────────────────

RPN::RPN() 
{}

RPN::RPN(const RPN& other) : _stack(other._stack) 
{}

RPN& RPN::operator=(const RPN& other) 
{
    if (this != &other)
        _stack = other._stack;
    return *this;
}

RPN::~RPN() 
{}

// ─── evaluate ───────────────────────────────────────────────────────────────────

void RPN::evaluate(const std::string& expr) 
{
    // clear any previous state
    while (!_stack.empty())
        _stack.pop();

    std::istringstream iss(expr);
    std::string token;

    while (iss >> token) 
{
        if (token.length() == 1 && isdigit(static_cast<unsigned char>(token[0]))) 
{
            _stack.push(token[0] - '0');
        } else if (token == "+" || token == "-" || token == "*" || token == "/") 
{
            if (_stack.size() < 2)
                throw std::runtime_error("Error");
            int b = _stack.top(); _stack.pop();
            int a = _stack.top(); _stack.pop();
            int result;
            if      (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else {
                if (b == 0)
                    throw std::runtime_error("Error");
                result = a / b;
            }
            _stack.push(result);
        } else {
            throw std::runtime_error("Error");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    std::cout << _stack.top() << std::endl;
}

