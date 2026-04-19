/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inventory.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 18:11:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "defines.hpp"
# include "AMateria.hpp"

class Inventory
{
	private:
		std::vector<AMateria*> materias;
		static const Verbose verbose = FULL;
		unsigned int maxSize;

	public:
		Inventory();
		Inventory(const Inventory& other);
		virtual ~Inventory();
		Inventory& operator=(const Inventory& other);

		void addMateria(AMateria* m);
		void removeMateria(int idx);
		AMateria* getMateria(int idx) const;

		friend std::ostream& operator<<(std::ostream& os, const Inventory& obj);
};
