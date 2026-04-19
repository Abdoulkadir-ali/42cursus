/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:42:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/16 00:53:27 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <ctime>
#include <iostream>

class Zombie
{
public:
	Zombie(void);
	Zombie(std::string name);
	~Zombie(void);
	Zombie(const Zombie &src);

	void announce(void);
	void setName(std::string name);

private :
	std::string _name;
};

Zombie* zombieHorde( int N, std::string name );