/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:37:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "ICharacter.hpp"
# include "Inventory.hpp"

class Character : public ICharacter
{
	private:
		std::string name;
		Inventory inventory;
		static const Verbose verbose = RESTRICTED;

	public:
		Character(std::string const& name);
		Character(const Character& other);
		virtual ~Character();
		Character& operator=(const Character& other);

		std::string const& getName() const;
		void equip(AMateria* m);
		void unequip(int idx);
		void use(int idx, ICharacter& target);
		Inventory getInventory() const;
};

std::ostream& operator<<(std::ostream& os, const Character& obj);
