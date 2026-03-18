/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:15:47 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:15:48 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Print the current working directory.
 * @param args Unused builtin argument vector.
 * @param state Shell state used as a fallback source for PWD.
 * @return 0 on success, 1 when no directory can be reported.
 */
int	ft_pwd(char **args, t_shell_state *state)
{
	char	cwd[1024];
	char	*pwd;

	(void)args;
	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putendl_fd(cwd, 1);
		return (0);
	}
	pwd = ft_get_env("PWD", state->envp);
	if (pwd)
	{
		ft_putendl_fd(pwd, 1);
		return (0);
	}
	perror("pwd");
	return (1);
}
