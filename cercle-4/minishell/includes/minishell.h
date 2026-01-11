/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 20:07:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/11 03:54:48 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"
#include "executor.h"

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>

#ifndef DEBUG
# define DEBUG 0
#endif

void	debug_printf(const char *format, ...);
char	*get_command_line(void);
