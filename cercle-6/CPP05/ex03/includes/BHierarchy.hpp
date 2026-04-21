#pragma once

#include <iostream>
#include <sstream>
#include <string>


class BHierarchy
{
	protected:
		const std::string name;
		std::string type;
		int minGrade;
		int maxGrade;

	public:
		BHierarchy();
		BHierarchy(const std::string &name, const std::string &type, int minG = 1, int maxG = 150);
		virtual ~BHierarchy();

		const std::string &getName(void) const;
		const std::string &getType(void) const;
		int getMinGrade(void) const;
		int getMaxGrade(void) const;

		std::string showGradeRange(void) const;
		void validateGradeRange(int minG, int maxG);

		virtual void showAttributes(void) const;

		class GradeTooHighException : public std::exception {
		public:
			virtual const char* what() const throw();
		};

		class GradeTooLowException : public std::exception {
		public:
			virtual const char* what() const throw();
		};

		class InvalidGradeRangeException : public std::exception {
		public:
			virtual const char* what() const throw();
		};

};

std::ostream &operator<<(std::ostream& out, const BHierarchy &instance);
 

