/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 23:30:52 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 23:31:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <stdexcept>
# include <iostream>

template <typename T>
class Array
{
	public:
		Array(void);
		Array(unsigned int n);
		Array(Array const &other);
		~Array(void);

		Array &operator=(Array const &other);
		T       &operator[](unsigned int index);
		T const &operator[](unsigned int index) const;

		unsigned int size(void) const;

	private:
		T            *_data;
		unsigned int  _size;
};

# include "Array.tpp"

#endif
