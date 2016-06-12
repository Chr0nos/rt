/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_cone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/12 19:12:58 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/12 19:36:03 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_cone(t_obj *obj, size_t ac, char **av)
{
	double			size;
	t_v4d			bsize;

	if (ac < 4)
		return (1);
	ft_strtoupper(av[S_COLOR_POS]);
	size = ft_atod(av[PROP_SIZE]);
	((t_cone*)obj->content)->size = (float)size;
	((t_cone*)obj->content)->color = yolo_setup_color(av[CONE_COLOR]);
	bsize = (t_v4d){cos(1.0472) * size / 2.0,
		sin(1.0472) * size / 2.0, size, 1.0};
	obj->hitbox = (t_box){(float)(obj->trans.w.x - bsize.x),
		(float)(obj->trans.w.x + bsize.x),
		(float)(obj->trans.w.y - bsize.y),
		(float)(obj->trans.w.y + bsize.y),
		(float)(obj->trans.w.z),
		(float)(obj->trans.w.z + size)};
	return (0);
}
