/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 19:14:54 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 17:10:49 by abdoali          ###   ########.fr       */
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

/* validate_line over t_nodes */
bool	validate_line_nodes(t_nodes *av, char *format)
{
	size_t	i;
	char	*tok;

	i = 0;
	while (format[i])
	{
		tok = ft_nodes_get(av, i);
		if (!tok)
			return (ft_puterror("Missing fields"));
		if (format[i] == 'v' && !is_valid_vector(tok))
			return (ft_puterror("Bad vector"));
		if (format[i] == 'f' && !is_valid_float(tok))
			return (ft_puterror("Bad float"));
		if (format[i] == 'c' && !is_valid_rgb(tok))
			return (ft_puterror("Bad RGB"));
		if (format[i] == 'i' && !is_valid_int(tok))
			return (ft_puterror("Bad int"));
		i++;
	}
	if (ft_nodes_get(av, i))
		return (ft_puterror("Too many arguments"));
	return (true);
}