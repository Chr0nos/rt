/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 18:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2018/12/28 19:04:34 by snicolet         ###   ########.fr       */
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
	t_obj				*cam;
	struct s_quaternion	*q;

	cam = rt->root->content;
	q = &cam->transform.q;
	if (dir & (ROTATE_LEFT | ROTATE_RIGHT))
		cam->rotation.y += (dir & ROTATE_LEFT) ? -x : x;
	if (dir & (ROTATE_UP | ROTATE_DOWN))
		cam->rotation.x += (dir & ROTATE_UP) ? -x : x;
	if (dir & ROLL)
		cam->rotation.z += (dir & ROLL_LEFT) ? -x : x;
	if (dir & ROTATE_LEFT)
		*q = geo_quat_mult(*q, geo_quat_rot(cam->transform.axis.y, x));
	else if (dir & ROTATE_RIGHT)
		*q = geo_quat_mult(*q, geo_quat_rot(cam->transform.axis.y, -x));
	if (dir & ROTATE_UP)
		*q = geo_quat_mult(*q, geo_quat_rot(cam->transform.axis.x, x));
	else if (dir & ROTATE_DOWN)
		*q = geo_quat_mult(*q, geo_quat_rot(cam->transform.axis.x, -x));
	if (dir & ROLL_LEFT)
		*q = geo_quat_mult(*q, geo_quat_rot(cam->transform.axis.z, -x));
	else if (dir & ROLL_RIGHT)
		*q = geo_quat_mult(*q, geo_quat_rot(cam->transform.axis.z, x));
	cam->trans = geo_quat_tomatrix_offset(*q, cam->trans.w);
	cam->transform.matrix = cam->trans;
	cam->transform.axis = (struct s_world){
		.x = geo_apply_v3d(AXIS_X, &cam->trans),
		.y = geo_apply_v3d(AXIS_Y, &cam->trans),
		.z = geo_apply_v3d(AXIS_Z, &cam->trans)
	};
}

void	camera_save(t_rt *rt)
{
	if (rt->keyboard & MENU)
	{
		menu_camera_save(rt);
		return ;
	}
	if ((!rt->root) || (!(t_obj*)rt->root->content))
		return ;
	((t_camera*)((t_obj*)rt->root->content)->content)->origin =
		((t_obj*)rt->root->content)->trans;
	((t_camera*)((t_obj*)rt->root->content)->content)->origin_rot =
		((t_obj*)rt->root->content)->rotation;
}

int		camera_reset(t_rt *rt)
{
	t_obj		*obj;
	t_camera	*cam;

	if (rt->keyboard & MENU)
		return (menu_camera_reset(rt));
	if (!(obj = rt->root->content))
		return (0);
	cam = obj->content;
	obj->trans = cam->origin;
	obj->rotation = cam->origin_rot;
	obj->transform.q = geo_quat_from_rot(
		(t_v3d){obj->rotation.x, obj->rotation.y, obj->rotation.z});
	// obj->trans = geo_quat_tomatrix_offset(cam->q, obj->trans.w);
	rt->keyboard |= FORCE_DISPLAY;
	return (0);
}
