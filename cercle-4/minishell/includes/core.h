/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:16:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/26 13:36:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

// PACKAGE
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define SIGNAL_INTERACTIVE 1
# define SIGNAL_BLOCKING 2
# define SIGNAL_HEREDOC 3

typedef struct s_shell_state
{
	int					exit_code;
	int					interactive_shell;
	int					syntax_error;
	int					expansion_error;
	char				**envp;
}						t_shell_state;

extern int				g_last_signal;

// CUSTOM
# include "exec.h"
# include "input.h"
# include "libft.h"
# include "parsing.h"

void					setup_signals(int mode);
int						set_error(int code, const char *msg);
int						main(int ac, char **av, char **envp);
int						init_shell(char **envp, char ***heap_env, t_shell_state *state);
void					add_shlvl_to_env(char **envp);

#endif