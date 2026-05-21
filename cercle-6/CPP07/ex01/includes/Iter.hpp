/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 23:30:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 23:30:45 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

#include <cstddef>
#include <iostream>

template <typename T, typename F>
void iter(T *array, std::size_t const len, F func)
{
	for (std::size_t i = 0; i < len; i++)
		func(array[i]);
}

template <typename T>
void print(T const &elem)
{
	std::cout << elem << std::endl;
}

template <typename T>
void increment(T &elem)
{
	elem++;
}

#endif
