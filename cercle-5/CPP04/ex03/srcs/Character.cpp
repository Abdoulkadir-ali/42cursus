#include "Character.hpp"

Character::Character(std::string const& name) : name(name)
{
	if (verbose == FULL)
		std::cout << "Character " << name << " created" << std::endl;
}

Character::Character(const Character& other) : name(other.name), inventory(other.inventory)
{
	if (verbose == FULL)
		std::cout << "Character " << name << " copied" << std::endl;
}

Character::~Character()
{
	if (verbose == FULL)
		std::cout << "Character " << name << " destroyed" << std::endl;
}

Character& Character::operator=(const Character& other)
{
	if (this != &other)
	{
		name = other.name;
		inventory = other.inventory;
	}
	return *this;
}

std::string const& Character::getName() const
{
	return name;
}

void Character::equip(AMateria* m)
{
	inventory.addMateria(m);
}

void Character::unequip(int idx)
{
	inventory.removeMateria(idx);
}

void Character::use(int idx, ICharacter& target)
{
	AMateria* m = inventory.getMateria(idx);
	if (m)
		m->use(target);
}

std::ostream& operator<<(std::ostream& os, const Character& obj)
{
	os << "Character " << obj.getName() << " with " << obj.inventory;
	return os;
}
