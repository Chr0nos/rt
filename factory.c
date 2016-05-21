/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:00:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/21 19:44:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

t_uint				rt_sizeof(t_type type)
{
	if (type == CUBE)
		return (sizeof(t_obj) + sizeof(t_cube));
	if (type == PLAN)
		return (sizeof(t_obj) + sizeof(t_plan));
	if (type == SPHERE)
		return (sizeof(t_obj) + sizeof(t_sphere));
	else if (type == CAMERA)
		return (sizeof(t_obj) + sizeof(t_camera));
	return (0);
}

t_obj				*rt_factory_alloc(t_type type, t_obj *parent)
{
	static t_uint		lastid = 1;
	const t_uint		size = rt_sizeof(type);
	t_obj				*obj;

	if (!size)
		return (NULL);
	else if (!(obj = malloc(size)))
		return (NULL);
	obj->type = type;
	obj->next = NULL;
	obj->childs = NULL;
	obj->parent = parent;
	obj->content = (void*)((unsigned long)obj + sizeof(t_obj));
	obj->id = lastid++;
	obj->trans = draw_make_matrix_identity();
	return (rt_obj_addchild(parent, obj));
}
