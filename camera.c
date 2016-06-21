/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 18:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/21 22:15:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"
#include "menu.h"

t_obj	*rt_obj_getcamera(t_obj *obj)
{
	t_obj	*x;
	t_obj	*z;

	if (obj->type == CAMERA)
		return (obj);
	else if (obj)
	{
		x = obj->childs;
		while (x)
		{
			if (x->type == CAMERA)
				return (x);
			else if ((z = rt_obj_getcamera(x)))
				return (z);
			x = x->next;
		}
	}
	return (NULL);
}

void	rt_update_camera(t_v2i geometry, t_camera *cam)
{
	t_v2d	tmp;

	cam->fovx = ((double)geometry.x / (double)geometry.y) * cam->fov;
	cam->steppx = (t_v2d){cam->fovx / (double)geometry.x,
		cam->fov / (double)geometry.y};
	cam->rayreset = (t_v4d){
		cam->fovx / 2.0,
		cam->fov / 2.0,
		0.0,
		0.0};
	tmp = (t_v2d){
		((double)geometry.x / (double)geometry.y) * sin((double)cam->fov),
		sin((double)cam->fov)};
	cam->rayfix = (t_v4d){ tmp.x / 2.0, tmp.y / 2.0,
		tmp.x / (double)geometry.x, tmp.y / (double)geometry.y};
}

void	camera_rotate(t_rt *rt, const double x, const int dir)
{
	t_obj	*cam;

	cam = rt->root->content;
	if (dir & (ROTATE_LEFT | ROTATE_RIGHT))
		cam->rotation.y += (dir & ROTATE_LEFT) ? -x : x;
	if (dir & (ROTATE_UP | ROTATE_DOWN))
		cam->rotation.x += (dir & ROTATE_UP) ? -x : x;
	if (dir & ROLL)
		cam->rotation.z += (dir & ROLL_LEFT) ? -x : x;
	cam->trans = draw_matrix_multiply_axes_m4(
		cam->rotation, (t_v4d){1.0, 1.0, 1.0, 1.0}, cam->trans.w);
}

void	camera_save(t_obj *camera)
{
	t_camera	*cam;

	cam = camera->content;
	cam->origin_rot = camera->rotation;
	cam->origin = camera->trans;
}

int		camera_reset(t_rt *rt)
{
	t_obj		*obj;
	t_camera	*cam;

	obj = rt->root->content;
	cam = obj->content;
	obj->trans = cam->origin;
	obj->rotation = cam->origin_rot;
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}
