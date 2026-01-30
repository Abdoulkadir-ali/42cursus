/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:34:40 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 15:55:15 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"

void	print_index(t_index i)
{
	printf("Index\tx:%zu\ty%zu\n", i.x, i.y);
}

// int	main(void)
// {
// 	print_index(create_index(15, 15));
// 	return (0);
// }
