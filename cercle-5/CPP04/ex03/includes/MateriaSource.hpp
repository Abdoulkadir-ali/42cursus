/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:31:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "IMateriaSource.hpp"
# include "defines.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		AMateria*	templates[4];
		static const size_t maxLearned = 4;
		static const Verbose verbose = RESTRICTED;

	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		virtual ~MateriaSource();
		MateriaSource& operator=(const MateriaSource& other);

		void learnMateria(AMateria* m);
		AMateria* createMateria(std::string const& type);
};

std::ostream& operator<<(std::ostream& os, const MateriaSource& obj);
