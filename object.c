/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:18:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/21 00:28:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
