/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 00:08:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/13 17:41:47 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <stdlib.h>

unsigned int		rt_sizeobj(t_type type)
{
	unsigned int		p;
	const t_typesize	sizes[] = {
		(t_typesize){CUBE, sizeof(struct s_cube)},
		(t_typesize){PLAN, sizeof(struct s_plan)},
		(t_typesize){SPHERE, sizeof(struct s_sphere)},
		(t_typesize){CONE, sizeof(struct s_cone)},
		(t_typesize){CAMERA, sizeof(struct s_camera)},
		(t_typesize){CYL, sizeof(struct s_cyl)}
	};

	p = 6;
	while (p--)
		if (sizes[p].type == type)
			return (sizeof(t_obj) + (unsigned int)sizes[p].size);
	return (sizeof(t_obj));
}

t_obj				*rt_factory_alloc(t_type type, t_obj *parent)
{
	static t_uint		lastid = 1;
	const t_uint		size = rt_sizeobj(type);
	t_obj				*obj;

	if (!size)
		return (NULL);
	if (!(obj = malloc(size)))
		return (NULL);
	rt_obj_init(obj, type);
	if (type == ROOT)
	{
		rt_box_update(obj);
		return (obj);
	}
	obj->id = lastid++;
	obj->parent = parent;
	obj->content = (void*)((unsigned long)obj + sizeof(t_obj));
	rt_debug(obj, 0);
	if (type & VISIBLE)
		((t_cube*)obj->content)->color = COLOR_BLACK;
	return (rt_obj_addchild(parent, obj));
}
