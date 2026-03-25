/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Execute.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: copilot <copilot@example.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/20 10:30:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AForm.hpp"

void AForm::execute(Bureaucrat const & executor) const
{
    if (!this->isSigned)
        throw AForm::NotSignedException();
    if (executor.getGrade() > this->requiredGradeToExecute)
        throw AForm::ExecGradeTooLowException();
    this->executeAction();
}
