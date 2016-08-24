/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_camera.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 18:14:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/24 18:51:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "parser.h"
#include "libft.h"

void		yolo_camera_save(t_obj *camera)
{
	t_camera	*cam;

	cam = camera->content;
	cam->origin_rot = camera->rotation;
	cam->origin = camera->trans;
}

int			yolo_setup_camera(t_obj *obj, size_t ac, char **av)
{
	double		fov;
	t_camera	*cam;

	if (ac < CAMERA_OR_Z)
	{
		ft_putstr("error: failed to setup camera\n");
		return (1);
	}
	cam = ((t_camera*)obj->content);
	if ((ac <= 6) || ((fov = ft_atod(av[6])) < MINFOV) || (fov > MAXFOV))
		fov = 49.124;
	cam->fov = deg2rad(fov);
	rt_obj_rotate(obj, (t_v4d){
		deg2rad(ft_atod(av[CAMERA_OR_X])),
		deg2rad(ft_atod(av[CAMERA_OR_Y])),
		deg2rad(ft_atod(av[CAMERA_OR_Z])),
		1.0});
	obj->cfgbits |= SDB_FOV | SDB_ROT;
	yolo_camera_save(obj);
	return (0);
}
