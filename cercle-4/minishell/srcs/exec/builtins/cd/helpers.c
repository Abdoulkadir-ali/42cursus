/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 02:44:37 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 03:15:37 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*get_env_val_simple(char *key, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (envp && envp[i])
	{
		if (!ft_strncmp(envp[i], key, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*get_cwd_dup(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (ft_strdup(""));
}

char	*resolve_home(char **envp)
{
	char			*path;
	struct passwd	*pw;

	path = get_env_val_simple("HOME", envp);
	if (path)
	{
		if (path[0] == '\0')
			return (get_cwd_dup());
		return (path);
	}
	pw = getpwuid(getuid());
	if (pw && pw->pw_dir)
		return (pw->pw_dir);
	ft_puterror("cd: HOME not set\n");
	return (NULL);
}
