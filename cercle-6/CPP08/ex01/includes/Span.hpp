/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/20 22:50:10 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/20 22:50:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

# include <vector>
# include <stdexcept>
# include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>

class Span
{
public:
	Span(unsigned int n);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(int n);

	template <typename Iterator>
	void addRange(Iterator begin, Iterator end)
	{
		while (begin != end)
		{
			addNumber(*begin);
			++begin;
		}
	}

	int shortestSpan() const;
	int longestSpan() const;

private:
	unsigned int      _max;
	std::vector<int>  _data;
};

#endif
