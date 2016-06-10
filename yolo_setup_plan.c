/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_plan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:15:36 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/10 18:20:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int			yolo_setup_plan(t_obj *obj, size_t ac, char **av)
{
	if (ac < 7)
		return (1);
	ft_strtoupper(av[PLAN_COLOR]);
	((t_plan*)obj->content)->color = yolo_setup_color(av[PLAN_COLOR]);
	obj->rotation = (t_v4d){
		deg2rad(ft_atod(av[PLAN_OR_X])),
		deg2rad(ft_atod(av[PLAN_OR_Y])),
		deg2rad(ft_atod(av[PLAN_OR_Z])),
		0.0
	};
	obj->trans = draw_matrix_multiply_axes_m4(
		obj->rotation,
		(t_v4d){1.0, 1.0, 1.0, 1.0},
		obj->trans.w);
	draw_putm4(obj->trans, 6);
	return (0);
}
