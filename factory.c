/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 00:08:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/21 14:47:27 by alhote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include "mesh.h"
#include <stdlib.h>

unsigned int		rt_sizeobj(t_type type)
{
	unsigned int		p;
	const t_typesize	sizes[] = {
		(t_typesize){CUBE, sizeof(struct s_cube)},
		(t_typesize){PLAN, sizeof(struct s_plan)},
		(t_typesize){SPHERE, sizeof(struct s_sphere)},
		(t_typesize){CONE, sizeof(struct s_cone)},
		(t_typesize){CONE_INF, sizeof(struct s_cone_inf)},
		(t_typesize){CAMERA, sizeof(struct s_camera)},
		(t_typesize){CYL, sizeof(struct s_cyl)},
		(t_typesize){LIGHTTYPE, sizeof(struct s_plight)},
		(t_typesize){SETTING, sizeof(struct s_setting)},
		(t_typesize){TRIANGLE, sizeof(struct s_triangle)},
		(t_typesize){MESH, sizeof(struct s_mesh)}
	};

	p = 11;
	while (p--)
		if (type & sizes[p].type)
			return (sizeof(t_obj) + (unsigned int)sizes[p].size);
	return (sizeof(t_obj));
}

unsigned int		rt_factory_getuid(void)
{
	static t_uint		lastid = 1;

	return (lastid++);
}

t_obj				*rt_factory_alloc(t_type type, t_obj *parent)
{
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
	obj->id = rt_factory_getuid();
	obj->parent = parent;
	obj->content = (void*)((unsigned long)obj + sizeof(t_obj));
	if (type & VISIBLE)
		((t_cube*)obj->content)->color = COLOR_BLACK;
	if (obj->type == PLAN)
		((t_plan*)obj->content)->heightmap = NULL;
	return (rt_obj_addchild(parent, obj));
}
