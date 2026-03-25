/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:10:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/20 10:15:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "BHierarchy.hpp"
class AForm;

class Bureaucrat : public BHierarchy
{
    private:
        int grade;

    public:
        Bureaucrat();
        Bureaucrat(const std::string &name, const std::string &type, int grade, int minGrade = 1, int maxGrade = 150);
        Bureaucrat(const Bureaucrat& other);
        ~Bureaucrat(void);

        const std::string &getName(void) const;
        const std::string &getType(void) const;
        int getGrade(void) const;
        int getMinGrade(void) const;
        int getMaxGrade(void) const;

        bool isValidGrade(int grade) const;
        void setGrade(int new_grade);
        void demote(void);
        void promote(void);
        void executeForm(AForm const & form) const;

        std::string showCurrentGrade(void) const;
        void showAttributes(void) const;

        // use exceptions declared in BHierarchy
};

std::ostream &operator<<(std::ostream& out, const Bureaucrat &instance);


