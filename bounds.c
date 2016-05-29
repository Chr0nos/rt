/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounds.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/29 03:26:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/29 04:06:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_bounds_update_in(t_obj *obj, void *userdata)
{
	(void)obj;
	(void)userdata;
	update_cube(&obj->bounds, &obj->hitbox);
	update_cube(&obj->parent->bounds, &obj->hitbox);
}

void		rt_bounds_update(t_obj *node)
{
	rt_node_foreach(node, INFIX, &rt_bounds_update_in, NULL);
}
