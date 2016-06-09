/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:18:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/09 05:52:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

t_obj		*rt_obj_makeroot(void)
{
	t_obj	*root;

	if (!(root = malloc(sizeof(t_obj))))
		return (NULL);
	root->id = 0;
	root->parent = NULL;
	root->childs = NULL;
	root->next = NULL;
	root->content = NULL;
	root->type = ROOT;
	root->hitbox = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	root->bounds = (t_box){0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	root->normal = NULL;
	root->inters = NULL;
	root->trans = draw_make_matrix_m4_identity();
	root->rotation = (t_v4d){0.0, 0.0, 0.0, 1.0};
	rt_box_update(root);
	return (root);
}

void		rt_obj_free(t_obj *obj, unsigned int level)
{
	t_obj	*next;
	t_obj	*x;

	if ((!level) && (obj->parent))
		rt_obj_delchild(obj->parent, obj);
	obj->parent = NULL;
	x = obj->childs;
	while (x)
	{
		next = x->next;
		rt_obj_free(x, level + 1);
		x = next;
	}
	free(obj);
}
