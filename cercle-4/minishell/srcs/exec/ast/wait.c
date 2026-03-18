/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:17 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:18 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Convert a raw waitpid status into the shell-visible exit code.
 * @param status Raw status value returned by waitpid.
 * @return Shell-compatible exit status, including signal offsets.
 */
int	handle_wait_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			write(1, "\n", 1);
		else if (WTERMSIG(status) == SIGQUIT)
			ft_puterror("Quit (core dumped)\n");
		return (128 + WTERMSIG(status));
	}
	return (1);
}
