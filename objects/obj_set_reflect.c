/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_set_reflect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:06:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/21 17:32:59 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "mesh.h"

int				rt_obj_set_reflect(t_obj *obj, unsigned char reflect)
{
	if (obj->type == CUBE)
		((t_cube*)obj->content)->reflect = reflect;
	else if (obj->type == SPHERE)
		((t_sphere*)obj->content)->reflect = reflect;
	else if (obj->type == CONE)
		((t_cone*)obj->content)->reflect = reflect;
	else if (obj->type == CONE_INF)
		((t_cone_inf*)obj->content)->reflect = reflect;
	else if (obj->type == PLAN)
		((t_plan*)obj->content)->reflect = reflect;
	else if (obj->type == CYL)
		((t_cyl*)obj->content)->reflect = reflect;
	else if (obj->type == SETTING)
		((t_setting*)obj->content)->reflect = reflect;
	else if (obj->type == TRIANGLE)
		((t_triangle*)obj->content)->reflect = reflect;
	else if (obj->type == MESH)
		((t_mesh*)obj->content)->reflect = reflect;
	else
		return (0);
	return (1);
}

unsigned char	rt_obj_get_reflect(const t_obj *obj)
{
	IFRET__(obj->type == CUBE, ((t_cube*)obj->content)->reflect);
	IFRET__(obj->type == SPHERE, ((t_sphere*)obj->content)->reflect);
	IFRET__(obj->type == CONE, ((t_cone*)obj->content)->reflect);
	IFRET__(obj->type == CONE_INF, ((t_cone_inf*)obj->content)->reflect);
	IFRET__(obj->type == PLAN, ((t_plan*)obj->content)->reflect);
	IFRET__(obj->type == CYL, ((t_cyl*)obj->content)->reflect);
	IFRET__(obj->type == SETTING, ((t_setting*)obj->content)->reflect);
	IFRET__(obj->type == TRIANGLE, ((t_triangle*)obj->content)->reflect);
	IFRET__(obj->type == MESH, ((t_mesh*)obj->content)->reflect);
	return (0);
}
