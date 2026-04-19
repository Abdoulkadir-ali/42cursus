#include "Cure.hpp"

Cure::Cure() : AMateria("cure")
{
	if (verbose == FULL)
		std::cout << "Cure constructor called" << std::endl;
}

Cure::Cure(const Cure& other) : AMateria(other)
{
	if (verbose == FULL)
		std::cout << "Cure copy constructor called" << std::endl;
}

Cure::~Cure()
{
	if (verbose == FULL)
		std::cout << "Cure destructor called" << std::endl;
}

Cure& Cure::operator=(const Cure& other)
{
	if (verbose == FULL)
		std::cout << "Cure assignation operator called" << std::endl;
	(void)other;
	return *this;
}

AMateria* Cure::clone() const
{
	return new Cure(*this);
}

void Cure::use(ICharacter& target)
{
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
