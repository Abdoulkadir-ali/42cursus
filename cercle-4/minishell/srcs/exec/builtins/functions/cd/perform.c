/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbranco <hbranco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/18 02:14:49 by hbranco           #+#    #+#             */
/*   Updated: 2026/03/18 02:14:50 by hbranco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/**
 * @brief Capture the old working directory before changing directories.
 * @param state Shell state used to inspect PWD.
 * @return Newly allocated previous working directory string.
 */
static char	*get_oldpwd(t_shell_state *state)
{
	char	*oldpwd;

	oldpwd = ft_get_env("PWD", state->envp);
	if (!oldpwd || oldpwd[0] == '\0')
		oldpwd = get_cwd_dup();
	else
		oldpwd = ft_strdup(oldpwd);
	return (oldpwd);
}

/**
 * @brief Change directory using the logical normalized path when possible.
 * @param path Requested cd target path.
 * @param state Shell state used for logical normalization.
 * @return Result of chdir.
 */
static int	change_directory(char *path, t_shell_state *state)
{
	char	*norm_path;
	int		rc;

	norm_path = normalize_logical(path, state);
	if (norm_path)
		rc = chdir(norm_path);
	else
		rc = chdir(path);
	free(norm_path);
	return (rc);
}

/**
 * @brief Report a cd failure and release temporary directory strings.
 * @param path Original path requested by the user.
 * @param oldpwd Saved previous working directory.
 * @param norm_path Extra normalized path to release when provided.
 * @return Always returns 1.
 */
static int	handle_cd_error(char *path, char *oldpwd, char *norm_path)
{
	ft_puterror("cd: %s: ", path);
	perror(NULL);
	free(oldpwd);
	free(norm_path);
	return (1);
}

/**
 * @brief Compute the new PWD value after a successful directory change.
 * @param path Requested cd target path.
 * @param state Shell state used for logical normalization.
 * @return Newly allocated directory string for the updated PWD value.
 */
static char	*get_newpwd(char *path, t_shell_state *state)
{
	char	cwd[1024];
	char	*newpwd;

	newpwd = normalize_logical(path, state);
	if (!newpwd)
	{
		if (getcwd(cwd, sizeof(cwd)))
			newpwd = ft_strdup(cwd);
		else
			newpwd = ft_strdup("");
	}
	return (newpwd);
}

/**
 * @brief Perform the directory change and update PWD and OLDPWD.
 * @param path Requested cd target path.
 * @param state Active shell state whose environment is updated.
 * @return 0 on success, 1 when chdir fails.
 */
int	perform_cd(char *path, t_shell_state *state)
{
	char	*oldpwd;
	int		rc;
	char	*newpwd;

	oldpwd = get_oldpwd(state);
	rc = change_directory(path, state);
	if (rc == -1)
		return (handle_cd_error(path, oldpwd, NULL));
	newpwd = get_newpwd(path, state);
	ft_set_env("OLDPWD", oldpwd, state);
	ft_set_env("PWD", newpwd, state);
	free(oldpwd);
	free(newpwd);
	return (0);
}
