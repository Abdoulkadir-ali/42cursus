/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 01:13:18 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_echo(char **args)
{
    int	i;
    int	newline;
    int	k;

    newline = 1;
    i = 1;
    while (args[i] && ft_strncmp(args[i], "-n", 2) == 0)
    {
        k = 1;
        while (args[i][k] == 'n')
            k++;
        if (args[i][k] == '\0')
        {
            newline = 0;
            i++;
        }
        else
            break ;
    }
    while (args[i])
    {
        ft_putstr_fd(args[i], 1);
        if (args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (newline)
        ft_putchar_fd('\n', 1);
    return (0);
}
