/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 00:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/10 21:04:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HELPERS_TIME_H
# define HELPERS_TIME_H

# include <stddef.h>
# include <sys/time.h>
# include_next <time.h>

/*
** Returns the current wall-clock time in milliseconds.
*/
long long	now_ms(void);

#endif
