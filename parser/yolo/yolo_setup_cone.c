/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 19:12:58 by qloubier          #+#    #+#             */
/*   Updated: 2016/08/24 18:50:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_cone(t_obj *obj, size_t ac, char **av)
{
	double			size;
	double			angle;
	t_v4d			bsize;

	if (ac < 4)
		return (1);
	ft_strtoupper(av[S_COLOR_POS]);
	size = ft_atod(av[PROP_SIZE]);
	if ((ac <= CONE_ANGLE) ||
		((angle = deg2rad(ft_atod(av[CONE_ANGLE]))) < 0.02)
		|| (angle > 3.0))
		angle = 1.0472;
	((t_cone*)obj->content)->size = (float)size;
	bsize = (t_v4d){angle, cos(angle / 2.0), sin(angle / 2.0), 0.0};
	bsize.w = bsize.y / bsize.z;
	((t_cone*)obj->content)->angle = bsize;
	((t_cone*)obj->content)->color = yolo_setup_color(av[CONE_COLOR]);
	bsize = (t_v4d){bsize.w * size,
		bsize.w * size, size, 1.0};
	obj->hitbox = (t_box){(float)(obj->trans.w.x - bsize.x),
		(float)(obj->trans.w.x + bsize.x),
		(float)(obj->trans.w.y - size), (float)(obj->trans.w.y),
		(float)(obj->trans.w.z - bsize.y), (float)(obj->trans.w.z + bsize.y)};
	obj->cfgbits |= SDB_ANGLE | SDB_COLOR | SDB_SIZE;
	return (0);
}
