/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 18:16:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:41:43 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

int main()
{
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());
	AMateria* tmp;
	

	std::cout << "___________ Creating character... __________" << std::endl;
	ICharacter* me = new Character("me");
	Character* copy = new Character(*static_cast<Character*>(me));

	std::cout << *copy << std::endl;
	std::cout << "___________ Equipping materias on copy... __________" << std::endl;
	tmp = src->createMateria("ice");
	copy->equip(tmp);
	tmp = src->createMateria("cure");
	copy->equip(tmp);

	std::cout << *copy << std::endl;
	ICharacter* bob = new Character("bob");

	std::cout << "___________ Using materias on copy... __________" << std::endl;
	copy->use(0, *bob);
	copy->use(1, *bob);


	std::cout << "___________ Unequipping materias from copy... __________" << std::endl;
	std::cout << *copy << std::endl;
	copy->unequip(0);
	std::cout << *copy << std::endl;
	copy->unequip(1); // Invalid index, should be handled gracefully
	copy->unequip(5); // Invalid index, should be handled gracefully
	copy->unequip(0); // Valid index
	copy->unequip(0); // Valid indexm but already unequipped, should be handled gracefully

	std::cout << "___________ Final state of copy... __________" << std::endl;
	std::cout << *copy << std::endl;
	std::cout << "Original : "  << *static_cast<Character*>(me) << std::endl;


	std::cout << "___________ Deleting ... __________" << std::endl;
	delete bob;
	delete me;
	delete copy;
	delete src;
	return 0;
}
