/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 15:11:09 by abdoali           #+#    #+#             */
/*   Updated: 2026/05/08 01:56:14 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include "libft.h"

typedef struct s_app	t_app;

void					safe_exit(const char *msg, t_app *app, int code, ...);
void					ft_puterror(const char *message);
void					print_error(const char *msg, ...);
void					cleanup_app(t_app *app);

#endif
