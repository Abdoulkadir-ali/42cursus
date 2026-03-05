/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:44:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:06:02 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

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
