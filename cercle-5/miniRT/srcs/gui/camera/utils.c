/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antigravity <antigravity@gemini.google.com> +#    +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 00:00:00 by antigravity       #+#    #+#             */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

/**
 * Clamps the field of view between 10 and 170 degrees.
 * @param fov Pointer to the FOV value (in degrees).
 */
void	clamp_fov(double *fov)
{
	if (*fov < 10.0)
		*fov = 10.0;
	if (*fov > 170.0)
		*fov = 170.0;
}
