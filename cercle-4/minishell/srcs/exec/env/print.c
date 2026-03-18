/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:16:16 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:16:18 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Print one environment entry using the export display format.
 * @param entry Raw environment entry in KEY=VALUE or KEY form.
 * @return This function does not return a value.
 */
static void	print_env_entry(char *entry)
{
	char	*eq;

	if (!entry)
		return ;
	ft_putstr_fd("declare -x ", 1);
	eq = ft_strchr(entry, '=');
	if (eq)
	{
		write(1, entry, eq - entry);
		write(1, "=\"", 2);
		ft_putstr_fd(eq + 1, 1);
		write(1, "\"\n", 2);
	}
	else
	{
		ft_putstr_fd(entry, 1);
		write(1, "\n", 1);
	}
}

/**
 * @brief Print the environment sorted in the format expected by export.
 * @param envp NULL-terminated environment array to display.
 * @return This function does not return a value.
 */
void	print_sorted_env(char **envp)
{
	t_nodes	*list;
	int		i;
	t_nodes	*tmp;

	list = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "_=", 2) != 0 && ft_strcmp(envp[i], "_") != 0)
			ft_lstadd_back(&list, ft_lstnew(ft_strdup(envp[i])));
		i++;
	}
	ft_lstsort(&list, (int (*)(void *, void *))ft_strcmp);
	tmp = list;
	while (tmp)
	{
		print_env_entry(tmp->content);
		tmp = tmp->next;
	}
	ft_lstclear(&list, free);
}
