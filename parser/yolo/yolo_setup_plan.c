/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_plan.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:15:36 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:49:28 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int			yolo_setup_plan(t_obj *obj, size_t ac, char **av)
{
	if (ac < PLAN_TEXTURE)
		return (1);
	ft_strtoupper(av[PLAN_COLOR]);
	((t_plan*)obj->content)->color = yolo_setup_color(av[PLAN_COLOR]);
	rt_obj_rotate(obj, (t_v4d){
		deg2rad(ft_atod(av[PLAN_OR_X])),
		deg2rad(ft_atod(av[PLAN_OR_Y])),
		deg2rad(ft_atod(av[PLAN_OR_Z])),
		0.0});
	obj->cfgbits |= SDB_COLOR | SDB_ROT;
	return (0);
}
