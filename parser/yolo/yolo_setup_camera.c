/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:14:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/16 12:32:02 by snicolet         ###   ########.fr       */
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
	rt_obj_rotate(obj,
		(t_v4d){
			deg2rad(ft_atod(av[CAMERA_OR_X])),
			deg2rad(ft_atod(av[CAMERA_OR_Y])),
			deg2rad(ft_atod(av[CAMERA_OR_Z])),
			1.0
		});
	((t_camera*)obj->content)->origin = obj->trans;
	return (0);
}
