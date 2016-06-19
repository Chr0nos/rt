/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_plight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/18 13:31:13 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/19 22:49:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_plight(t_obj *obj, size_t ac, char **av)
{
	double			tmp;

	if (ac < 3)
		return (1);
	if ((ac <= PLIGHT_POWER) || ((tmp = ft_atod(av[PLIGHT_POWER])) < 0.0))
		tmp = MID_LIGHT_POWER;
	((t_plight *)obj->content)->intensity = tmp;
	tmp = 0.0;
	if (ac > PLIGHT_RADIUS)
		tmp = ft_atod(av[PLIGHT_RADIUS]);
	((t_plight *)obj->content)->radius = (float)tmp;
	if (ac <= PLIGHT_COLOR)
	{
		((t_plight *)obj->content)->color = 0xffffff;
		return (0);
	}
	ft_strtoupper(av[PLIGHT_COLOR]);
	((t_plight *)obj->content)->color = yolo_setup_color(av[PLIGHT_COLOR]);
	return (0);
}
