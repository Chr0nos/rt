/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yolo_setup_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/08 17:41:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/13 11:45:29 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		yolo_setup_type(t_obj *obj, int mode, void *userdata)
{
	(void)mode;
	(void)userdata;
	if (obj->type == SPHERE)
	{
		obj->inters = &rt_sphere_inter;
		obj->normal = &rt_sphere_normal;
	}
	else if (obj->type == PLAN)
	{
		obj->inters = &rt_plane_inter;
		obj->normal = &rt_plane_normale;
	}
	else if (obj->type == CONE)
	{
		obj->inters = &rt_cone_inter;
		obj->normal = &rt_cone_normale;
	}
	else if (obj->type == CYL)
	{
		obj->inters = &rt_cyl_inter;
		obj->normal = &rt_cyl_normale;
	}
	else if (obj->type == CUBE)
		obj->inters = &rt_cube_inter;
	return (OK);
}
