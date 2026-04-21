/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 07:10:46 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 20:14:24 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <sstream>
#include <string>


class Bureaucrat
{        
    private:
        const std::string name;
        std::string type;
        int grade;
        int minGrade;
        int maxGrade;
        
    public:
        //Init
        Bureaucrat();
        Bureaucrat(const std::string &name, const std::string &type, int grade, int minGrade = 1, int maxGrade = 150);
        Bureaucrat(const Bureaucrat& other);
        ~Bureaucrat(void);

        //Getters
        const std::string &getName(void) const;
        const std::string &getType(void) const;
        int getGrade(void) const;
        int getMinGrade(void) const;
        int getMaxGrade(void) const;

        //Setters
        bool isValidGrade(int grade) const;
        void setGrade(int new_grade);
        void demote(void);
        void promote(void);

        //Prints
        std::string showGradeRange(void) const;
        std::string showCurrentGrade(void) const;
        void showAttributes(void) const;
        void validateGradeRange(int minG, int maxG);

        class GradeTooHighException :
            public std::exception {
                public:
                    virtual const char* what() const throw();
            };

        class GradeTooLowException : 
            public std::exception {
                public:
                    virtual const char* what() const throw();
                };

        class InvalidGradeRangeException : 
            public std::exception {
                    public: 
                        virtual const char* what() const throw();
                    };
};

std::ostream &operator<<(std::ostream& out, const Bureaucrat &instance);


