/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 01:20:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/13 01:17:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	get_env_index(char *key, char **envp)
{
    int i;
    int len;

    if (!key || !envp)
        return (-1);
    len = ft_strlen(key);
    i = 0;
    while (envp && envp[i])
    {
        if (ft_strncmp(envp[i], key, len) == 0 && (envp[i][len] == '=' || envp[i][len] == '\0'))
            return (i);
        i++;
    }
    return (-1);
}

int	is_valid_ident(char *str)
{
    int i;

    if (!str || !str[0])
        return (0);
    i = 0;
    if (!ft_isalpha(str[i]) && str[i] != '_')
        return (0);
    i++;
    while (str[i] && str[i] != '=')
    {
        if (!ft_isalnum(str[i]) && str[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

int	ft_set_env(char *key, char *value, char ***envp)
{
    char *new_entry;
    int idx;
    int count;
    char **new_env;
    int i;

    if (!key || !envp || !*envp)
        return (1);
    new_entry = ft_strjoin(key, "=");
    if (value)
    {
        char *tmp = new_entry;
        new_entry = ft_strjoin(new_entry, value);
        free(tmp);
    }
    idx = get_env_index(key, *envp);
    if (idx != -1)
    {
        free((*envp)[idx]);
        (*envp)[idx] = new_entry;
    }
    else
    {
        count = 0;
        while ((*envp)[count])
            count++;
        new_env = ft_calloc(count + 2, sizeof(char *));
        i = -1;
        while (++i < count)
            new_env[i] = (*envp)[i];
        new_env[count] = new_entry;
        free(*envp);
        *envp = new_env;
    }
    return (0);
}
