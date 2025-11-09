/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:11:33 by abdoali           #+#    #+#             */
/*   Updated: 2025/11/09 16:01:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute_command(char *cmd)
{
	extern char	**environ;
	char		**args;
	int			saved_errno;

	args = parse_command(cmd);
	if (!args || !args[0])
	{
		if (args)
			free_args(args);
		exit(127);
	}
	execve(args[0], args, environ);
	execvp(args[0], args);
	saved_errno = errno;
	perror(args[0]);
	free_args(args);
	if (saved_errno == ENOENT)
		exit(127);
	exit(126);
}
