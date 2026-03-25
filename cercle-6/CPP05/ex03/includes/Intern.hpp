/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 11:00:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 11:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include "AForm.hpp"

class Intern {
public:
    Intern();
    Intern(const Intern&);
    ~Intern();

    Intern& operator=(const Intern&);

    AForm* makeForm(const std::string &formName, const std::string &target) const;
private:
    static AForm* createForm(const std::string &formName, const std::string &target);
};

