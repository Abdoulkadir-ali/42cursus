/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:17:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 21:06:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook()
    : _name("")
    , _size(0)
    , _creation_date(std::time(NULL))
    , _column_sizes(10)
    , _column_amount(4)
{
    _print_fields[0] = "index";
    _print_fields[1] = "first_name";
    _print_fields[2] = "last_name";
    _print_fields[3] = "nickname";
}

PhoneBook::PhoneBook(const std::string &name, unsigned int size)
    : _name(name)
    , _size(MAX(size, MAX_CONTACTS))
    , _creation_date(std::time(NULL))
    , _column_sizes(10)
    , _column_amount(4)
{
    _print_fields[0] = "index";
    _print_fields[1] = "first_name";
    _print_fields[2] = "last_name";
    _print_fields[3] = "nickname";
}

PhoneBook::~PhoneBook()
{
}

PhoneBook::PhoneBook(const PhoneBook &phone_book)
    : _name(phone_book._name)
    , _size(phone_book._size)
    , _creation_date(phone_book._creation_date)
    , _column_sizes(phone_book._column_sizes)
    , _column_amount(phone_book._column_amount)
{
    for (unsigned int i = 0; i < MAX_CONTACTS; ++i)
        _contacts[i] = phone_book._contacts[i];
    for (unsigned int i = 0; i < 4; ++i)
        _print_fields[i] = phone_book._print_fields[i];
}

void PhoneBook::AddContact(const Contact &new_contact)
{
    if (_size >= MAX_CONTACTS)
    {
        for (unsigned int i = MAX_CONTACTS - 1; i > 0; --i)
            _contacts[i] = _contacts[i - 1];
        _contacts[0] = new_contact;
    }
    else 
    {
        for (unsigned int i = _size; i > 0; --i)
            _contacts[i] = _contacts[i - 1];
        _contacts[0] = new_contact;
        ++_size;
    }
}

void PhoneBook::PrintRow(unsigned int columns, const std::string fields[4])
{
    for (unsigned int i = 0; i < columns; i++)
    {
        std::string s = fields[i];
        if (s.size() > 10)
            s = s.substr(0, 9) + ".";
        std::cout << "|" << std::setw(10) << std::right << s;
    }
    std::cout << "|" << std::endl;
}

void PhoneBook::PrintCharRow(char c, unsigned int width)
{
    for (unsigned int i = 0; i < width; i++)
        std::cout << c;
    std::cout << std::endl;
}

void PhoneBook::Print()
{
    unsigned int width = _column_amount * _column_sizes + _column_amount + 1;
    
    PrintCharRow('-', width);
    PrintRow(4, _print_fields);
    PrintCharRow('-', width);
    for (unsigned int i = 0; i < _size; ++i)
    {
        std::ostringstream idx_stream;
        idx_stream << i;
        std::string idx = idx_stream.str();
        std::string row[4] = { idx,
            _contacts[i].GetFirstName(),
            _contacts[i].GetLastName(),
            _contacts[i].GetNickname() };
        PrintRow(4, row);
    }
    PrintCharRow('-', width);
}

void PhoneBook::Add()
{
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone_number;
    std::string darkest_secret;

    while (first_name.empty())
    {
        std::cout << "First name: ";
        if (!std::getline(std::cin, first_name))
            return;
    }
    while (last_name.empty())
    {
        std::cout << "Last name: ";
        if (!std::getline(std::cin, last_name))
            return;
    }
    while (nickname.empty())
    {
        std::cout << "Nickname: ";
        if (!std::getline(std::cin, nickname))
            return;
    }
    while (phone_number.empty())
    {
        std::cout << "Phone number: ";
        if (!std::getline(std::cin, phone_number))
            return;
    }
    while (darkest_secret.empty())
    {
        std::cout << "Darkest secret: ";
        if (!std::getline(std::cin, darkest_secret))
            return;
    }
    AddContact(Contact(first_name, last_name, nickname, phone_number, darkest_secret));
}

void PhoneBook::Search()
{
    std::string line;
    unsigned long idx;
    char extra;
    
    if (_size == 0)
    {
        std::cout << "PhoneBook empty." << std::endl;
        return;
    }
    Print();
    std::cout << "Enter index to view: ";
    if (!std::getline(std::cin, line))
        return;
    std::istringstream iss(line);
    if (!(iss >> idx) || (iss >> extra))
    {
        std::cout << "Invalid index" << std::endl;
        return;
    }
    if (idx >= _size || idx >= MAX_CONTACTS)
    {
        std::cout << "Invalid index" << std::endl;
        return;
    }
    _contacts[idx].Print();
}

int PhoneBook::Run()
{
    std::string cmd;
    
    while (true)
    {
        std::cout << "Enter command (ADD, SEARCH, EXIT): ";
        if (!std::getline(std::cin, cmd))
            return 0;
        if (cmd == "ADD")
            Add();
        else if (cmd == "SEARCH")
            Search();
        else if (cmd == "EXIT")
            break;
        else
            continue;
    }
    return 0;
}

