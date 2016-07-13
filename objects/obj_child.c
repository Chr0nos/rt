/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:00:00 by snicolet          #+#    #+#             */
/*   Updated: 2016/07/13 12:51:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*rt_obj_addchild(t_obj *parent, t_obj *child)
{
	t_obj	*x;

	if (!parent)
		return (child);
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
