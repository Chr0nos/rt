/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:26:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/04 19:19:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_bounds_update_in(t_obj *obj, int mode, void *userdata)
{
	(void)userdata;
	if (mode == PREFIX)
		obj->bounds = obj->hitbox;
	else if (obj->parent)
		update_cube(&obj->parent->bounds, &obj->bounds);
}

void		rt_bounds_update(t_obj *node)
{
	rt_node_foreach(node, SUFFIX | PREFIX, &rt_bounds_update_in, NULL);
}
