/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_cyl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 11:19:24 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/15 18:08:47 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int					yolo_setup_cyl(t_obj *obj, size_t ac, char **av)
{
	double	radius;
	double	height;

	if (ac < CYL_TEXTURE + 1)
	{
		ft_putstr("error: failed to setup object type Cylinder\n");
		return (1);
	}
	ft_puttab((const char**)(unsigned long)av);
	ft_strtoupper(av[CYL_COLOR_POS]);
	((t_cyl*)obj->content)->radius = (float)ft_atod(av[PROP_SIZE]);
	((t_cyl*)obj->content)->height = (float)ft_atod(av[CYL_HEIGHT]);
	((t_cyl*)obj->content)->color = yolo_setup_color(av[CYL_COLOR_POS]);
	obj->texture = ft_atoi(av[CYL_TEXTURE]);
	obj->rotation = (t_v4d){deg2rad(ft_atod(av[CYL_OR_X])),
		deg2rad(ft_atod(av[CYL_OR_Y])),
		deg2rad(ft_atod(av[CYL_OR_Z])),
		1.0};
	obj->trans = draw_matrix_multiply_axes_m4(
			obj->rotation, (t_v4d){1.0, 1.0, 1.0, 1.0}, obj->trans.w);
	draw_putm4(obj->trans, 6);
	radius = (double)((t_cyl*)obj->content)->radius;
	height = (double)((t_cyl*)obj->content)->height;
/*		obj->hitbox = (t_box){
		(float)(obj->trans.w.x - radius), (float)(obj->trans.w.x + radius),
		(float)(obj->trans.w.y - height), (float)(obj->trans.w.y + height),
		(float)(obj->trans.w.z), (float)(obj->trans.w.z)};
	ft_putstr("5\n");
*/	return (0);
}
