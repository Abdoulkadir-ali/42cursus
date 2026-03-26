/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setlabel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/25 16:56:31 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include <string.h>
#include <stdlib.h>

void	widget_set_label(t_widget *widget, const char *label)
{
    if (label)
        widget->label = strdup(label);
}
