/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:05:31 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/01 02:00:08 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#include <string>
#include <ctime>
#include <iostream>
#include "Contact.hpp"

class PhoneBook
{
private:
		static const unsigned int MAX_CONTACTS = 8;
		std::string _name;
		unsigned int _size; // current number of contacts
		std::time_t _creation_date;
		Contact _contacts[MAX_CONTACTS];

public:
		PhoneBook();
		PhoneBook(const PhoneBook &phone_book);
		PhoneBook(const std::string &name, unsigned int size);
		~PhoneBook();

		void Add();
		void Search();
		// internal helper to insert a contact
		void AddContact(const Contact &new_contact);
		void PrintRow(unsigned int columns, const std::string fields[4]);
		void PrintCharRow(char c, unsigned int width);
		void Print();
		void Exit();
		int Run();

		std::string _print_fields[4];
		unsigned int _column_sizes;
		unsigned int _column_amount;
};
