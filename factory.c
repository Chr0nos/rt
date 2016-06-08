/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alhote <alhote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 00:08:40 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/08 18:53:07 by alhote           ###   ########.fr       */
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
		(t_typesize){CAMERA, sizeof(struct s_camera)}
	};

	p = 4;
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

	if (type == ROOT)
		return (rt_obj_makeroot());
	if (!size)
		return (NULL);
	if (!(obj = malloc(size)))
		return (NULL);
	obj->type = type;
	obj->next = NULL;
	obj->childs = NULL;
	obj->parent = parent;
	obj->content = (void*)((unsigned long)obj + sizeof(t_obj));
	obj->id = lastid++;
	obj->trans = draw_make_matrix_m4_identity();
	obj->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->rotation = (t_v4d){0.0, 0.0, 0.0, 0.0};
	obj->inters = NULL;
	obj->normal = NULL;
	return (rt_obj_addchild(parent, obj));
}
