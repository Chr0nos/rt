/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:14:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/13 15:24:30 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

int		yolo_setup_camera(t_obj *obj, size_t ac, char **av)
{
	double	fov;

	if (ac < CAMERA_OR_Z)
	{
		ft_putstr("error: failed to setup camera\n");
		return (1);
	}
	if ((ac <= 6) || ((fov = ft_atod(av[6])) < MINFOV) || (fov > MAXFOV))
		fov = 49.124;
	((t_camera*)obj->content)->fov = deg2rad(fov);
	obj->rotation = (t_v4d){deg2rad(ft_atod(av[CAMERA_OR_X])),
		deg2rad(ft_atod(av[CAMERA_OR_Y])),
		deg2rad(ft_atod(av[CAMERA_OR_Z])),
		1.0};
	obj->trans = draw_matrix_multiply_axes_m4(
		obj->rotation,
		(t_v4d){1.0, 1.0, 1.0, 1.0}, obj->trans.w);
	((t_camera*)obj->content)->origin = obj->trans;
	return (0);
}
