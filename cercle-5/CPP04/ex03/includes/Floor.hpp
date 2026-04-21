/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Floor.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 02:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/21 02:13:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "Inventory.hpp"

class Floor : public Inventory
{
	private:
		static const size_t maxSize = 10000;
		AMateria*	items[maxSize];
		int			lastIndex;
		void clear();
		void copyFrom(const Floor& other);

	public:
		Floor();
		Floor(const Floor& other);
		virtual ~Floor();
		Floor& operator=(const Floor& other);

		void drop(AMateria* m);
};
