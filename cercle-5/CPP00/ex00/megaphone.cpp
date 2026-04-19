/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 19:08:33 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/14 19:13:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <iostream>

int	main(int argc, char **argv)
{
	int i = 0;
	unsigned int j = 0;
	std::string str;

	if (argc < 2)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}
	argv++;
	while (argv[i])
	{
		str = argv[i];
		j = 0;
		while (j < str.length())
			std::cout << static_cast<char>(toupper(str[j++]));
		if (i < argc - 2)
			std::cout << ' ';
		i++;
	}
	std::cout << std::endl;	
	return (0);
}
