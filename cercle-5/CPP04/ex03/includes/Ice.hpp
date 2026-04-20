/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 13:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 01:31:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "AMateria.hpp"

class Ice : public AMateria
{
	private:
		static const Verbose verbose = RESTRICTED;

	public:
		Ice();
		Ice(const Ice& other);
		virtual ~Ice();
		Ice& operator=(const Ice& other);

		AMateria* clone() const;
		void use(ICharacter& target);
};

std::ostream& operator<<(std::ostream& os, const Ice& obj);
