/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 19:52:50 by abdoali           #+#    #+#             */
/*   Updated: 2026/04/29 19:52:50 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZATION_H
# define OPTIMIZATION_H

# include "gameplay.h"

void	init_optimization(t_world *world);
void	update_optimization(t_world *world, int elapsed_us);

#endif
