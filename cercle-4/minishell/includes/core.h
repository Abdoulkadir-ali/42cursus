/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 06:16:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 22:09:09 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CORE_H
# define CORE_H

/**
 * @file core.h
 * @brief Top-Level Entry API
 * 
 * Central orchestration bridge pulling all primary subsystem APIs together.
 * Exposes the final binary execution loop allowing REPL transitions.
 */

// CUSTOM
# include "exec.h"
# include "input.h"
# include "libft.h"
# include "parsing.h"
# include "state.h"

int	minishell(int ac, char **av, char **envp);
int	main(int ac, char **av, char **envp);

#endif