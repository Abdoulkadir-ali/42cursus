/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setlabel.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdoali <abdoali@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 20:40:00 by copilot           #+#    #+#             */
/*   Updated: 2026/03/26 11:20:51 by abdoali          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

void	widget_set_label(t_widget *widget, const char *label)
{
    if (label)
        widget->label = strdup(label);
}
