/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:00:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/27 23:16:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"
#include <stdlib.h>

t_uint				rt_sizeof(t_type type)
{
	unsigned int		p;
	const t_typesize	sizes[] = {
		(t_typesize){CUBE, sizeof(t_cube)},
		(t_typesize){PLAN, sizeof(t_plan)},
		(t_typesize){SPHERE, sizeof(t_sphere)},
		(t_typesize){CAMERA, sizeof(t_camera)}
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
	ft_bzero(&obj->bounds, sizeof(t_box));
	ft_bzero(&obj->hitbox, sizeof(t_box));
	return (rt_obj_addchild(parent, obj));
}
