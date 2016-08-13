/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_count.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 15:55:19 by snicolet          #+#    #+#             */
/*   Updated: 2016/08/13 16:09:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "objects.h"

static int		rt_obj_count_foreach(t_obj *obj, int mode, void *userdata)
{
	unsigned int	*count_and_mask;

	(void)mode;
	count_and_mask = userdata;
	if (obj->type & count_and_mask[1])
		count_and_mask[0]++;
	return (OK);
}

unsigned int	rt_obj_count(t_obj *obj, unsigned int type_mask)
{
	unsigned int	count_and_mask[2];

	count_and_mask[0] = 0;
	count_and_mask[1] = type_mask;
	rt_node_foreach(obj, PREFIX, &rt_obj_count_foreach, count_and_mask);
	return (count_and_mask[0]);
}
