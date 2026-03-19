/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:33:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 07:18:00 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Shell entry point. Initializes state and hands over to minishell logic.
 * @param ac Argument count.
 * @param av Argument vector.
 * @param envp System environment variables.
 * @return Exit status of the shell session.
 */
int	main(int ac, char **av, char **envp)
{
	return (minishell(ac, av, envp));
}
