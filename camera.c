/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 18:08:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/01 21:42:19 by snicolet         ###   ########.fr       */
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
	double	fovy;

	fovy = (double)geometry.y / (double)geometry.x * (double)cam->fov;
	cam->steppx = (t_v2d){(double)cam->fov / (double)geometry.x,
		(double)fovy / (double)geometry.y};
	cam->rayreset = (t_v4f){cam->fov / 2.0f, (float) fovy / 2.0f, 0.0f, 0.0f};
}
