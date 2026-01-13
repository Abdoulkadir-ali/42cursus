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

extern char	**g_envp;
extern int	g_exit_code;
extern int	g_interactive_shell;

#endif
