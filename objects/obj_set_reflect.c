/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_set_reflect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/14 17:06:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/14 17:18:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

int		rt_obj_set_reflect(t_obj *obj, unsigned char reflect)
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
	else if (obj->type == TORE)
		((t_tore*)obj->content)->reflect = reflect;
	else
		return (0);
	return (1);
}
