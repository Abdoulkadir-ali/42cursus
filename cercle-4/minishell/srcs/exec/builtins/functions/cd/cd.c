/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:34 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:36 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Reject unsupported cd invocations with too many operands.
 * @param args Argument vector passed to the cd builtin.
 * @return 1 when the invocation is invalid, else 0.
 */
static int	validate_cd_args(char **args)
{
	if (args[1] && args[2])
	{
		ft_puterror("cd: too many arguments\n");
		return (1);
	}
	return (0);
}

/**
 * @brief Execute the cd builtin using the selected target path.
 * @param args Argument vector passed to cd.
 * @param state Active shell state whose directory variables are updated.
 * @return Builtin status for the directory change request.
 */
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

/**
 * @brief Duplicate the current working directory using getcwd.
 * @return Newly allocated current directory, or an empty string on failure.
 */
char	*get_cwd_dup(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		return (ft_strdup(cwd));
	return (ft_strdup(""));
}

/**
 * @brief Resolve the home directory used by cd with no explicit operand.
 * @param state Shell state used to inspect HOME.
 * @return Newly allocated home path, or NULL when no home is available.
 */
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
