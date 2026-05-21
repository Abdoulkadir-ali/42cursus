/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:50:39 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:50:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Span.hpp"

Span::Span(unsigned int n) : _max(n) {}

Span::Span(const Span& other) : _max(other._max), _data(other._data) {}

Span& Span::operator=(const Span& other)
{
	if (this != &other)
	{
		_max  = other._max;
		_data = other._data;
	}
	return *this;
}

Span::~Span() {}

void Span::addNumber(int n)
{
	if (_data.size() >= _max)
		throw std::runtime_error("Span is full");
	_data.push_back(n);
}

int Span::shortestSpan() const
{
	if (_data.size() < 2)
		throw std::runtime_error("Not enough elements to find a span");

	std::vector<int> sorted(_data);
	std::sort(sorted.begin(), sorted.end());

	int shortest = sorted[1] - sorted[0];
	for (std::size_t i = 2; i < sorted.size(); ++i)
	{
		int diff = sorted[i] - sorted[i - 1];
		if (diff < shortest)
			shortest = diff;
	}
	return shortest;
}

int Span::longestSpan() const
{
	if (_data.size() < 2)
		throw std::runtime_error("Not enough elements to find a span");

	int min = *std::min_element(_data.begin(), _data.end());
	int max = *std::max_element(_data.begin(), _data.end());
	return max - min;
}
