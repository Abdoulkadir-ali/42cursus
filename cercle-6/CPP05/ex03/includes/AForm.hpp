/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                           :+:      :+:    :+:   */
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

class AForm : public BHierarchy
{
    private:
        bool isSigned;
        int requiredGradeToSign;
        int requiredGradeToExecute;

    public:
        AForm();
        AForm(const std::string &name, const std::string &type, int signGrade, int execGrade, int minGrade = 1, int maxGrade = 150);
        AForm(const AForm& other);
        ~AForm(void);

        const std::string &getName(void) const;
        const std::string &getType(void) const;
        int getGrade(void) const;
        int getMinGrade(void) const;
        int getMaxGrade(void) const;

        bool isValidGrade(int grade) const;
        void beSigned(Bureaucrat &);

        void execute(Bureaucrat const & executor) const;

    protected:
        virtual void executeAction(void) const = 0;

    public:
        class NotSignedException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        class ExecGradeTooLowException : public std::exception {
        public:
            virtual const char* what() const throw();
        };

        std::string showCurrentGrade(void) const;
        std::string showRequiredGrade(void) const;
        void showAttributes(void) const;
};

std::ostream &operator<<(std::ostream& out, const AForm &instance);


