/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/15 04:49:41 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

// PACKAGE
# include <stdarg.h>
# include <stdio.h>

// CUSTOM
# include "libft.h"

int		ft_strmatch(char *s1, char *s2, int (*match)(char *, char *));
int		str_any(char *s1, char *s2);
void	ft_puterror(const char *fmt, ...);

#endif
