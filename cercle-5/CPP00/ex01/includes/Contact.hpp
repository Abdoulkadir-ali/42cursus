/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 20:21:01 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 21:04:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <iostream>
#include <string>
#include <ctime>

class Contact
{
private:
    std::string _first_name;
    std::string _last_name;
    std::string _nickname;
    std::string _phone_number;
    std::string _darkest_secret;
    std::time_t _creation_date;

public:
    Contact();
    Contact(const std::string &first_name, const std::string &last_name,
            const std::string &nickname, const std::string &phone_number,
            const std::string &darkest_secret);
    Contact(const Contact &contact);
    ~Contact();
    void Update(const std::string &first_name, const std::string &last_name,
                const std::string &nickname, const std::string &phone_number,
                const std::string &darkest_secret);
    void Print() const;
    std::string GetFirstName() const;
    std::string GetLastName() const;
    std::string GetNickname() const;
    std::string GetPhoneNumber() const;
    std::string GetDarkestSecret() const;
};