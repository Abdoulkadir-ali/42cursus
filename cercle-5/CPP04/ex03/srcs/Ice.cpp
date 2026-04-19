#include "Ice.hpp"

Ice::Ice() : AMateria("ice")
{
	if (verbose == FULL)
		std::cout << "Ice constructor called" << std::endl;
}

Ice::Ice(const Ice& other) : AMateria(other)
{
	if (verbose == FULL)
		std::cout << "Ice copy constructor called" << std::endl;
}

Ice::~Ice()
{
	if (verbose == FULL)
		std::cout << "Ice destructor called" << std::endl;
}

Ice& Ice::operator=(const Ice& other)
{
	if (verbose == FULL)
		std::cout << "Ice assignation operator called" << std::endl;
	(void)other;
	return *this;
}

AMateria* Ice::clone() const
{
	return new Ice(*this);
}

void Ice::use(ICharacter& target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}
