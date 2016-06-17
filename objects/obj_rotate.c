/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 14:01:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/17 14:04:27 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_obj		*rt_obj_rotate(t_obj *obj, const t_v4d radians)
{
	obj->rotation = draw_v4d_add(radians, obj->rotation);
	obj->trans = draw_matrix_multiply_axes_m4(radians,
		(t_v4d){1.0, 1.0, 1.0, 1.0},
		obj->trans.w);
	return (obj);
}
