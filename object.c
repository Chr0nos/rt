/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:18:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/16 18:19:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libft.h"

t_obj		*rt_obj_nparent(t_obj *obj, unsigned int n)
{
	while ((n--) && (obj->parent))
		obj = obj->parent;
	return (obj);
}

t_obj		*rt_obj_addchild(t_obj *parent, t_obj *child)
{
	t_obj	*x;

	x = parent->childs;
	if (!x)
		return (parent->childs = child);
	while (x->next)
		x = x->next;
	return (x->next = child);
}

t_obj		*rt_obj_delchild(t_obj *parent, t_obj *child)
{
	t_obj	*x;

	x = parent->childs;
	if (x == child)
		parent->childs = x->next;
	else
	{
		while ((x) && (x->next != child))
			x = x->next;
		if (x)
			x->next = child->next;
	}
	return (child);
}

t_obj		*rt_obj_init(t_obj *obj, t_type type)
{
	obj->id = 0;
	obj->type = type;
	obj->next = NULL;
	obj->childs = NULL;
	obj->content = NULL;
	obj->trans = draw_make_matrix_m4_identity();
	obj->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	obj->rotation = (t_v4d){0.0, 0.0, 0.0, 0.0};
	obj->inters = NULL;
	obj->normal = NULL;
	obj->parent = NULL;
	obj->texture = 0;
	return (obj);
}

t_obj		*rt_obj_rotate(t_obj *obj, const t_v4d radians)
{
	const t_v4d		zero = (t_v4d){0.0, 0.0, 0.0, 0.0};

	if (!ft_memcmp(&zero, &obj->rotation, sizeof(t_v4d)))
		obj->rotation = radians;
	else
		obj->rotation = draw_v4d_add(radians, obj->rotation);
	obj->trans = draw_matrix_multiply_axes_m4(radians,
		(t_v4d){1.0, 1.0, 1.0, 1.0},
		obj->trans.w);
	return (obj);
}
