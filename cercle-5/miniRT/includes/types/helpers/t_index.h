/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_index.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 14:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/03 14:07:11 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_INDEX_H
# define T_INDEX_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_index
{
	size_t	i;
	bool	error;
}	t_index;

#endif