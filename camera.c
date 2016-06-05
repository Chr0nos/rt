/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 18:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/05 21:49:40 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "keyboard.h"

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

	cam->fovy = ((float)geometry.y / (float)geometry.x) * cam->fov;
	cam->steppx = (t_v2d){(double)cam->fov / (double)geometry.x,
		(double)cam->fovy / (double)geometry.y};
	cam->rayreset = (t_v4d){
		(double)cam->fovy / 2.0,
		(double)cam->fov / 2.0,
		0.0,
		0.0};
	tmp = (t_v2d){1 - sin((double)cam->fov), 1 - sin((double)cam->fovy)};
	cam->rayfix = (t_v4d){ tmp.x / 2.0, tmp.y / 2.0,
		tmp.x / (double)geometry.x, tmp.y / (double)geometry.y};
}

void	camera_rotate(t_rt *rt, const double x, const int dir)
{
	t_obj			*cam;
	double			rad;

	cam = rt->root->content;
	rad = (dir & (ROTATE_LEFT | ROTATE_DOWN)) ? -x : x;
	if (dir & (ROTATE_LEFT | ROTATE_RIGHT))
		cam->rotation.x += rad;
	if (dir & (ROTATE_UP | ROTATE_DOWN))
		cam->rotation.y += rad;
	cam->trans = draw_matrix_multiply_axes_m4(
		cam->rotation, (t_v4d){1.0, 1.0, 1.0, 1.0}, cam->trans.w);
}
