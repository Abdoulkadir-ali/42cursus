/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 01:12:30 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	extra_print(char *kv)
{
    char *k;
    char *v;

    k = ft_strndup(kv, ft_strchr(kv, '=') - kv);
    v = ft_strdup(ft_strchr(kv, '=') + 1);
    ft_putstr_fd(k, 1);
    ft_putstr_fd("=\"", 1);
    ft_putstr_fd(v, 1);
    ft_putendl_fd("\"", 1);
    free(k);
    free(v);
}

int	ft_export(char **args)
{
    int i;

    if (!args || !args[1])
    {
        print_sorted_env();
        return (0);
    }
    i = 1;
    while (args[i])
    {
        if (ft_strchr(args[i], '='))
            env_add(args[i]);
        i++;
    }
    return (0);
}
