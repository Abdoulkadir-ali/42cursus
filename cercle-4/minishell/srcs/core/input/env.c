/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:56:11 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 03:56:13 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char **duplicate_env(char **envp)
{
    int env_count = 0;
    char **heap_env;
    int k;
    while (envp[env_count])
        env_count++;
    heap_env = malloc(sizeof(char *) * (env_count + 1));
    if (!heap_env)
        return NULL;
    k = 0;
    while (k < env_count)
    {
        heap_env[k] = ft_strdup(envp[k]);
        k++;
    }
    heap_env[k] = NULL;
    return heap_env;
}

int is_whitespace_only(char *str)
{
    while (str && *str)
    {
        if (!ft_isspace(*str))
            return (0);
        str++;
    }
    return (1);
}