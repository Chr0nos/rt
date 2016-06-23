/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:01:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/23 22:06:55 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*rt_obj_rotate(t_obj *obj, const t_v4d radians)
{
	obj->rotation = geo_addv4(radians, obj->rotation);
	obj->trans = geo_mk4_rotxyz(radians,
		(t_v4d){1.0, 1.0, 1.0, 1.0},
		obj->trans.w);
	return (obj);
}
