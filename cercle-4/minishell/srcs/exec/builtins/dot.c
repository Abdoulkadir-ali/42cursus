/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 05:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 04:58:49 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_dot(char **args, char ***envp)
{
	(void)envp;
	if (!args[1])
	{
		ft_puterror(".: filename argument required\n");
		ft_puterror(".: usage: . filename [arguments]\n");
		return (2);
	}
	return (0);
}
