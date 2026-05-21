/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.tpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:45:30 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:45:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_TPP
# define ARRAY_TPP

# include "Array.hpp"

template <typename T>
Array<T>::Array(void) : _data(NULL), _size(0) {}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n) {}

template <typename T>
Array<T>::Array(Array const &other) : _data(NULL), _size(0)
{
	*this = other;
}

template <typename T>
Array<T>::~Array(void)
{
	delete[] _data;
}

template <typename T>
Array<T> &Array<T>::operator=(Array const &other)
{
	if (this == &other)
		return *this;
	delete[] _data;
	_size = other._size;
	_data = new T[_size];
	for (unsigned int i = 0; i < _size; i++)
		_data[i] = other._data[i];
	return *this;
}

template <typename T>
T &Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of bounds");
	return _data[index];
}

template <typename T>
T const &Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of bounds");
	return _data[index];
}

template <typename T>
unsigned int Array<T>::size(void) const
{
	return _size;
}

#endif
