/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 13:33:35 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/09 23:36:39 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

/**
 * @brief Enter the minishell runtime from the program entry point.
 * @param ac Argument count received from the process launcher.
 * @param av Argument vector used for optional `-c` execution.
 * @param envp Environment array inherited from the parent process.
 * @return Exit status returned by the minishell runtime.
 */
int	main(int ac, char **av, char **envp)
{
	return (minishell(ac, av, envp));
}
