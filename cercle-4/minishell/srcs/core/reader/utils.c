/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 22:50:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 17:26:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

char	*append_line(char *line, char *new_line)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(line, "\n");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, new_line);
	free(temp);
	return (result);
}

char	*get_prompt(int is_initial)
{
	if (!isatty(STDIN_FILENO))
		return (NULL);
	if (is_initial)
		return ("minishell> ");
	return ("> ");
}
