#include "AMateria.hpp"

AMateria::AMateria(std::string const& type) : type(type)
{
	if (verbose == FULL)
		std::cout << "AMateria type constructor called" << std::endl;
}

AMateria::AMateria(const AMateria& other)
{
	if (verbose == FULL)
		std::cout << "AMateria copy constructor called" << std::endl;
	*this = other;
}

AMateria::~AMateria()
{
	if (verbose == FULL)
		std::cout << "AMateria destructor called" << std::endl;
}

AMateria& AMateria::operator=(const AMateria& other)
{
	if (verbose == FULL)
		std::cout << "AMateria assignation operator called" << std::endl;
	if (this != &other)
		this->type = other.type;
	return *this;
}

std::string const& AMateria::getType() const
{
	return this->type;
}

void AMateria::use(ICharacter& target)
{
	(void)target;
}

std::ostream& operator<<(std::ostream& os, const AMateria& obj)
{
	os << "Materia type: " << obj.getType();
	return os;
}
