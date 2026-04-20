/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:31:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "defines.hpp"
# include "AMateria.hpp"

class Inventory
{
	private:
		AMateria*	materias[4];
		static const Verbose verbose = RESTRICTED;
		static const size_t maxSize = 4;

	public:
		Inventory();
		Inventory(const Inventory& other);
		virtual ~Inventory();
		Inventory& operator=(const Inventory& other);

		void addMateria(AMateria* m);
		void removeMateria(int idx);
		AMateria* getMateria(int idx) const;
		size_t getCount() const;
};

std::ostream& operator<<(std::ostream& os, const Inventory& obj);
