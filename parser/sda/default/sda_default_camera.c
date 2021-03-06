/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sda_default_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/24 17:28:18 by snicolet          #+#    #+#             */
/*   Updated: 2016/09/03 21:58:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sda.h"
#include "parser.h"
#include "objects.h"
#include "quaternion.h"

void	sda_default_camera(t_rt *rt, t_obj *obj)
{
	t_camera	*cam;

	(void)rt;
	if (!(obj->type & CAMERA))
		return ;
	cam = obj->content;
	if (!(obj->cfgbits & SDB_FOV))
		cam->fov = -49.124;
	obj->transform.q = geo_quat_from_rot(
		(t_v3d){obj->rotation.x, obj->rotation.y, obj->rotation.z});
	yolo_camera_save(obj);
}
