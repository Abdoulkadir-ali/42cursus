/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:35:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/26 04:56:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
		ft_putendl_fd(entry, 1);
}

void	print_sorted_env(char **envp)
{
	t_nodes	*list;
	int		i;
	t_nodes	*tmp;

	list = NULL;
	i = 0;
	while (envp[i])
	{
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
