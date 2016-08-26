/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_nexttype.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 18:22:22 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/26 04:10:05 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"

static int	rt_obj_nexttype_foreach(t_obj *obj, int mode, void *userdata)
{
	t_obj_lookup	*look;

	(void)mode;
	look = userdata;
	if (obj == look->current)
	{
		look->lock = 1;
		return (OK);
	}
	if ((look->lock) && (obj->type & look->type))
	{
		look->next = obj;
		return (STOP_ALL);
	}
	return (OK);
}

t_obj		*rt_obj_nexttype(t_obj *node, t_obj *current, unsigned int type)
{
	t_obj_lookup	look;

	look.type = type;
	look.lock = (current) ? 0 : 1;
	look.current = current;
	look.next = NULL;
	rt_node_foreach(node, PREFIX, &rt_obj_nexttype_foreach, &look);
	return (look.next);
}
