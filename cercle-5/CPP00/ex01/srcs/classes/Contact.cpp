/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:17:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 21:05:06 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Contact.hpp"
#include <iostream>

Contact::Contact()
	: _first_name("")
	, _last_name("")
	, _nickname("")
	, _phone_number("")
	, _darkest_secret("")
	, _creation_date(std::time(NULL))
{
}

Contact::~Contact()
{
}

Contact::Contact(const Contact &contact)
	: _first_name(contact._first_name)
	, _last_name(contact._last_name)
	, _nickname(contact._nickname)
	, _phone_number(contact._phone_number)
	, _darkest_secret(contact._darkest_secret)
	, _creation_date(contact._creation_date)
{
}

Contact::Contact(const std::string &first_name, const std::string &last_name,
	const std::string &nickname, const std::string &phone_number,
	const std::string &darkest_secret)
	: _first_name(first_name)
	, _last_name(last_name)
	, _nickname(nickname)
	, _phone_number(phone_number)
	, _darkest_secret(darkest_secret)
	, _creation_date(std::time(NULL))
{
}

void Contact::Update(const std::string &first_name, const std::string &last_name,
	const std::string &nickname, const std::string &phone_number,
	const std::string &darkest_secret)
{
	_first_name = first_name;
	_last_name = last_name;
	_nickname = nickname;
	_phone_number = phone_number;
	_darkest_secret = darkest_secret;
	_creation_date = std::time(NULL);
}

void Contact::Print() const
{
	std::cout << "First name: " << _first_name << std::endl;
	std::cout << "Last name: " << _last_name << std::endl;
	std::cout << "Nickname: " << _nickname << std::endl;
	std::cout << "Phone number: " << _phone_number << std::endl;
	std::cout << "Darkest secret: " << _darkest_secret << std::endl;
}

std::string Contact::GetFirstName() const { return _first_name; }
std::string Contact::GetLastName() const { return _last_name; }
std::string Contact::GetNickname() const { return _nickname; }
std::string Contact::GetPhoneNumber() const { return _phone_number; }
std::string Contact::GetDarkestSecret() const { return _darkest_secret; }
