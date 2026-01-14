/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/14 17:46:52 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// PACKAGE
# include <stdio.h>

// CUSTOM
# include "core.h"
# include "exec.h"
# include "lib.h"
# include "libft.h"
# include "parsing.h"


# ifndef DEBUG
#  define DEBUG 0
# endif


extern char	**g_envp;
extern int	g_exit_code;
extern int	g_interactive_shell;

#endif
