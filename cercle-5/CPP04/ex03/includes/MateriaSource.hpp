/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 18:11:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "IMateriaSource.hpp"
# include "defines.hpp"

class MateriaSource : public IMateriaSource
{
	private:
		std::vector<AMateria*> templates;
		static const size_t maxLearned = 4;
		static const Verbose verbose = FULL;

	public:
		MateriaSource();
		MateriaSource(const MateriaSource& other);
		virtual ~MateriaSource();
		MateriaSource& operator=(const MateriaSource& other);

		void learnMateria(AMateria* m);
		AMateria* createMateria(std::string const& type);

		friend std::ostream& operator<<(std::ostream& os, const MateriaSource& obj);
};
