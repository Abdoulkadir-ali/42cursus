/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:35:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/13 02:54:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export.h"

static char **make_sorted_copy(char **envp, int count)
{
    char **sorted;
    int i;

    sorted = malloc(sizeof(char *) * (count + 1));
    if (!sorted)
        return (NULL);
    i = -1;
    while (++i < count)
        sorted[i] = envp[i];
    sorted[count] = NULL;
    return (sorted);
}

static void sort_string_array(char **arr, int count)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    while (i < count - 1)
    {
        j = 0;
        while (j < count - i - 1)
        {
            if (ft_strncmp(arr[j], arr[j + 1], ft_strlen(arr[j]) + ft_strlen(arr[j + 1])) > 0)
            {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

static void print_env_entry(char *entry)
{
    char *eq;

    if (!entry)
        return ;
    if (ft_strncmp(entry, "_=", 2) == 0)
        return ;
    ft_putstr_fd("declare -x ", 1);
    eq = ft_strchr(entry, '=');
    if (eq)
    {
        write(1, entry, eq - entry);
        write(1, "=\"", 3);
        ft_putstr_fd(eq + 1, 1);
        write(1, "\"\n", 2);
    }
    else
        ft_putendl_fd(entry, 1);
}

void print_sorted_env(char **envp)
{
    int count;
    char **sorted;
    int i;

    count = 0;
    while (envp[count])
        count++;
    sorted = make_sorted_copy(envp, count);
    if (!sorted)
        return ;
    sort_string_array(sorted, count);
    i = 0;
    while (i < count)
    {
        print_env_entry(sorted[i]);
        i++;
    }
    free(sorted);
}
