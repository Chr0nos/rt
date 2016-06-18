/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/18 13:03:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

double			rt_light_pow(t_render *r, t_obj *obj, t_obj *light, t_v4d lnor)
{
	const t_v4d		nor = obj->normal(obj, &(r->intersection));

	(void)light;
	return (draw_v4d_len(draw_v4d_add(nor, lnor)) - 1.0);
}
