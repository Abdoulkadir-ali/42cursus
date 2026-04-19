#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	if (verbose == FULL)
		std::cout << "MateriaSource constructor called" << std::endl;
}

MateriaSource::MateriaSource(const MateriaSource& other)
{
	if (verbose == FULL)
		std::cout << "MateriaSource copy constructor called" << std::endl;
	*this = other;
}

MateriaSource::~MateriaSource()
{
	for (size_t i = 0; i < templates.size(); i++)
		delete templates[i];
	if (verbose == FULL)
		std::cout << "MateriaSource destructor called" << std::endl;
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other)
{
	if (verbose == FULL)
		std::cout << "MateriaSource assignation operator called" << std::endl;
	if (this != &other)
	{
		for (size_t i = 0; i < templates.size(); i++)
			delete templates[i];
		templates.clear();
		for (size_t i = 0; i < other.templates.size(); i++)
			templates.push_back(other.templates[i]->clone());
	}
	return *this;
}

void MateriaSource::learnMateria(AMateria* m)
{
	if (m && templates.size() < maxLearned)
		templates.push_back(m);
}

AMateria* MateriaSource::createMateria(std::string const& type)
{
	for (size_t i = 0; i < templates.size(); i++)
	{
		if (templates[i]->getType() == type)
			return templates[i]->clone();
	}
	return 0;
}

std::ostream& operator<<(std::ostream& os, const MateriaSource& obj)
{
	(void)obj;
	os << "MateriaSource";
	return os;
}
