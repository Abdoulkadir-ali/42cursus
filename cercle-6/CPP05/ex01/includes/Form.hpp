/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:10:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 09:46:58 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BHierarchy.hpp"
#include "Bureaucrat.hpp"

class Bureaucrat;

class Form : public BHierarchy
{
    private:
        bool isSigned;
        int requiredGradeToSign;
        int requiredGradeToExecute;

    public:
        Form();
        Form(const std::string &name, const std::string &type, int grade, int minGrade = 1, int maxGrade = 150);
        Form(const Form& other);
        ~Form(void);

        const std::string &getName(void) const;
        const std::string &getType(void) const;
        int getGrade(void) const;
        int getMinGrade(void) const;
        int getMaxGrade(void) const;

        bool isValidGrade(int grade) const;
        void beSigned(Bureaucrat &);

        std::string showCurrentGrade(void) const;
        std::string showRequiredGrade(void) const;
        void showAttributes(void) const;
};

std::ostream &operator<<(std::ostream& out, const Form &instance);


