/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 23:00:11 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/20 23:52:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdlib.h>

static unsigned int		rt_sizeof(enum e_type type)
{
	if (type == CUBE)
		return (sizeof(t_obj) + sizeof(t_cube));
	else if (type == PLAN)
		return (sizeof(t_obj) + sizeof(t_plan));
	else if (type == SPHERE)
		return (sizeof(t_obj) + sizeof(t_sphere));
	return (0);
}

t_obj	*rt_factory_alloc(enum e_type type, t_obj *parent)
{
	const unsigned int	size = rt_sizeof(type);
	t_obj				*obj;
	static unsigned int	lastid = 1;

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
	return (rt_obj_addchild(parent, obj));
}
