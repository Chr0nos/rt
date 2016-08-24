/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_cone_inf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/30 11:04:14 by dboudy            #+#    #+#             */
/*   Updated: 2016/08/24 18:51:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_cone_inf(t_obj *obj, size_t ac, char **av)
{
	if (ac < CYL_TEXTURE)
	{
		ft_putstr("error: failed to setup object type Cylinder\n");
		return (1);
	}
	ft_strtoupper(av[CYL_COLOR_POS]);
	((t_cone_inf*)obj->content)->size = (float)ft_atod(av[PROP_SIZE]);
	((t_cone_inf*)obj->content)->color = yolo_setup_color(av[CYL_COLOR_POS]);
	rt_obj_rotate(obj,
		(t_v4d){deg2rad(ft_atod(av[CYL_OR_X])),
		deg2rad(ft_atod(av[CYL_OR_Y])),
		deg2rad(ft_atod(av[CYL_OR_Z])),
		1.0});
	obj->cfgbits |= SDB_COLOR | SDB_SIZE | SDB_ROT;
	return (0);
}
