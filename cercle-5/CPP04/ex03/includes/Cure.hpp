/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:31:53 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "AMateria.hpp"

class Cure : public AMateria
{
	private:
		static const Verbose verbose = RESTRICTED;

	public:
		Cure();
		Cure(const Cure& other);
		virtual ~Cure();
		Cure& operator=(const Cure& other);

		AMateria* clone() const;
		void use(ICharacter& target);
};

std::ostream& operator<<(std::ostream& os, const Cure& obj);
