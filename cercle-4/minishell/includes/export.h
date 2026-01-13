/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:30:00 by copilot           #+#    #+#             */
/*   Updated: 2026/01/13 03:24:44 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_H
# define EXPORT_H

# include "exec.h"

typedef struct s_export_ctx
{
	char	*key;
	char	*new_entry;
	char	*eq;
	int		append;
	int		idx;
}			t_export_ctx;

/* Public API used by other translation units */
void		print_sorted_env(char **envp);
int			process_export_arg(char *arg, char ***envp);

#endif
