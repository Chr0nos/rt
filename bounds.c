/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:26:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/29 05:07:35 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_bounds_update_in(t_obj *obj, void *userdata)
{
	(void)userdata;
	update_cube(&obj->bounds, &obj->hitbox);
	if (obj->parent)
		update_cube(&obj->parent->bounds, &obj->bounds);
}

void		rt_bounds_update(t_obj *node)
{
	rt_node_foreach(node, SUFFIX, &rt_bounds_update_in, NULL);
}
