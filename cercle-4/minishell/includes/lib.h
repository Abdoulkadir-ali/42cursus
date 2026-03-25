/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 03:25:06 by abdoali           #+#    #+#             */
/*   Updated: 2026/03/05 23:01:32 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

/**
 * @file lib.h
 * @brief Standard Data Primitives API
 * 
 * Exports universally safe string matching tools and formatting tools.
 * Completely stateless utility functions explicitly avoiding global contexts.
 */

// PACKAGE
# include <stdarg.h>
# include <stdio.h>

// CUSTOM
# include "libft.h"

void	ft_puterror(const char *fmt, ...);

#endif
