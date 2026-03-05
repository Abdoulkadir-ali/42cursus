/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:32:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	validate_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_puterror("cd: too many arguments\n");
		return (1);
	}
	return (0);
}

int	ft_cd(char **args, t_shell_state *state)
{
	char	*path;
	int		rc;

	if (validate_cd_args(args))
		return (1);
	path = get_cd_path(args, state);
	if (!path)
		return (1);
	rc = perform_cd(path, state);
	free(path);
	return (rc);
}

char	*get_cwd_dup(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (ft_strdup(""));
}

char	*resolve_home(t_shell_state *state)
{
	char			*path;
	struct passwd	*pw;

	path = ft_get_env("HOME", state->envp);
	if (path)
	{
		if (path[0] == '\0')
			return (get_cwd_dup());
		return (ft_strdup(path));
	}
	pw = getpwuid(getuid());
	if (pw && pw->pw_dir)
		return (ft_strdup(pw->pw_dir));
	ft_puterror("cd: HOME not set\n");
	return (NULL);
}
