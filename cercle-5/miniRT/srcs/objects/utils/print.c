/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:13:19 by abdoali           #+#    #+#             */
/*   Updated: 2026/01/30 19:19:57 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static const char	*type_name(int type)
{
	if (type == AMBIENT)
		return ("AMBIENT");
	if (type == CAMERA)
		return ("CAMERA");
	if (type == LIGHT)
		return ("LIGHT");
	if (type == SPHERE)
		return ("SPHERE");
	if (type == PLANE)
		return ("PLANE");
	if (type == SQUARE)
		return ("SQUARE");
	if (type == CYLINDER)
		return ("CYLINDER");
	return ("UNKNOWN");
}

void	print_object(t_object *obj)
{
	if (!obj)
		return ;
	printf("Object type: %s\n", type_name(obj->type));
	if (obj->transform)
	{
		printf(" position:\n");
		print_matrix(obj->transform->pos, &print_double);
		printf(" rotation:\n");
		print_matrix(obj->transform->rotation, &print_double);
		printf(" scale:\n");
		print_matrix(obj->transform->scale, &print_double);
	}
	if (obj->rgb)
	{
		printf(" rgb:\n");
		print_matrix(obj->rgb, &print_double);
	}
}

// int	main(void)
// {
// 	t_object	*o1;
// 	t_object	*o2;
// 	t_object	*o3;

// 	o1 = create_object();
// 	o1->type = SPHERE;
// 	matrix_set(o1->t, create_index(0, 0), &(double){1.0});
// 	matrix_set(o1->t, create_index(1, 0), &(double){2.0});
// 	matrix_set(o1->t, create_index(2, 0), &(double){3.0});
// 	matrix_set(o1->rgb, create_index(0, 0), &(double){1.0});
// 	matrix_set(o1->rgb, create_index(1, 0), &(double){0.0});
// 	matrix_set(o1->rgb, create_index(2, 0), &(double){0.0});
// 	o2 = create_object();
// 	o2->type = LIGHT;
// 	matrix_set(o2->t, create_index(0, 0), &(double){4.0});
// 	matrix_set(o2->t, create_index(1, 0), &(double){5.0});
// 	matrix_set(o2->t, create_index(2, 0), &(double){6.0});
// 	matrix_set(o2->rgb, create_index(0, 0), &(double){0.5});
// 	matrix_set(o2->rgb, create_index(1, 0), &(double){0.5});
// 	matrix_set(o2->rgb, create_index(2, 0), &(double){0.5});
// 	o3 = create_object();
// 	o3->type = PLANE;
// 	matrix_set(o3->t, create_index(0, 0), &(double){7.0});
// 	matrix_set(o3->t, create_index(1, 0), &(double){8.0});
// 	matrix_set(o3->t, create_index(2, 0), &(double){9.0});
// 	matrix_set(o3->rgb, create_index(0, 0), &(double){0.2});
// 	matrix_set(o3->rgb, create_index(1, 0), &(double){0.4});
// 	matrix_set(o3->rgb, create_index(2, 0), &(double){0.6});
// 	print_object(o1);
// 	print_object(o2);
// 	print_object(o3);
// 	destroy_object(o1);
// 	destroy_object(o2);
// 	destroy_object(o3);
// 	return (0);
// }