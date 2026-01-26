/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 13:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:38:49 by abdoali          ###   ########.fr       */
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

	if (validate_cd_args(args))
		return (1);
	path = get_cd_path(args, state);
	if (!path)
		return (1);
	return (perform_cd(path, state));
}
