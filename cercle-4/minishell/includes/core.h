/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:16:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/21 06:22:20 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

// PACKAGE
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// CUSTOM
# include "exec.h"
# include "input.h"
# include "libft.h"
# include "parsing.h"

# define SIGNAL_INTERACTIVE 1
# define SIGNAL_BLOCKING 2
# define SIGNAL_HEREDOC 3

typedef struct s_global_state
{
	char				**envp;
	int					exit_code;
	int					interactive_shell;
	int					expansion_error;
	int					last_signal;
}						t_global_state;

extern t_global_state	g_state;

void					setup_signals(int mode);
int						main(int ac, char **av, char **envp);

#endif