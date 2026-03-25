/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Errors.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

const char* AForm::NotSignedException::what() const throw()
{
    return "Form is not signed";
}

const char* AForm::ExecGradeTooLowException::what() const throw()
{
    return "Executor grade too low to execute form";
}

