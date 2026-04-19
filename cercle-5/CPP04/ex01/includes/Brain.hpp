/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/19 18:11:47 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once
# include "defines.hpp"

class Brain
{
	private:
		std::string ideas[100];
		static const Verbose verbose = FULL;

	public:
		Brain();
		Brain(const Brain& other);
		virtual ~Brain();
		Brain& operator=(const Brain& other);

		friend std::ostream& operator<<(std::ostream& os, const Brain& obj);
};
