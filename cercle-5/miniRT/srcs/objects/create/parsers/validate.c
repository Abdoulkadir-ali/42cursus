/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:14:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/29 07:20:23 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	validate_line(char **av, char *format)
{
	size_t	i;

	i = 0;
	while (format[i])
	{
		if (!av[i])
			return (ft_puterror("Missing fields"));
		if (format[i] == 'v' && !is_valid_vector(av[i]))
			return (ft_puterror("Bad vector"));
		if (format[i] == 'f' && !is_valid_float(av[i]))
			return (ft_puterror("Bad float"));
		if (format[i] == 'c' && !is_valid_rgb(av[i]))
			return (ft_puterror("Bad RGB"));
		if (format[i] == 'i' && !is_valid_int(av[i]))
			return (ft_puterror("Bad int"));
		i++;
	}
	if (av[i])
		return (ft_puterror("Too many arguments"));
	return (true);
}
