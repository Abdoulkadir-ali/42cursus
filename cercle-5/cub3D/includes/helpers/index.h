/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 21:00:00 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:53:55 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEX_H
# define INDEX_H

# include <stdbool.h>
# include <stddef.h>

typedef struct s_index
{
	size_t	i;
	bool	error;
}			t_index;

t_index		init_index(size_t i, bool error);
t_index		index_error(void);
t_index		index_success(size_t i);

#endif
