/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:09:49 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/19 02:52:17 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_H
# define STATE_H

# include "lib.h"
# include "libft.h"
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <unistd.h>

# ifndef SIGNAL_INTERACTIVE
#  define SIGNAL_INTERACTIVE 1
# endif

# ifndef SIGNAL_BLOCKING
#  define SIGNAL_BLOCKING 2
# endif
# ifndef SIGNAL_HEREDOC
#  define SIGNAL_HEREDOC 3
# endif
# ifndef SIGNAL_NON_INTERACTIVE
#  define SIGNAL_NON_INTERACTIVE 4
# endif

typedef struct s_shell_state
{
	int		exit_code;
	bool	interactive_shell;
	bool	syntax_error;
	bool	expansion_error;
	char	**envp;
}			t_shell_state;

extern int	g_last_signal;

void		handle_interactive(int sig);
void		handle_heredoc(int sig);
void		handle_sigterm(int sig);
int			event_hook(void);

void		setup_signal_mode(void (*handler)(int));
void		setup_child_signals(void);
void		setup_signals(int mode);
bool		init_shell(char **envp, t_shell_state *state);
void		add_shlvl_to_env(char **envp);
char		*ft_get_env(const char *key, char **envp);
int			get_env_index(char *key, t_shell_state *state);
char		**duplicate_envp(char **envp);

#endif