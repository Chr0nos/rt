/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 18:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/01 21:50:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	float	fovy;

	fovy = (float)geometry.y / (float)geometry.x * cam->fov;
	cam->steppx = (t_v2d){(double)cam->fov / (double)geometry.x,
		(double)fovy / (double)geometry.y};
	cam->rayreset = (t_v4d){
		(double)cam->fov / 2.0,
		(double)fovy / 2.0,
		0.0,
		0.0};
}
