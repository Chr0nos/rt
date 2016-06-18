/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/17 21:32:07 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

static double	rt_veclen(t_v4d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double			rt_light_pow(t_render *r, t_obj *obj, t_obj *light, t_v4d lnor)
{
	const t_v4d		nor = obj->normal(obj, &(r->intersection));

	(void)light;
	return (rt_veclen(draw_v4d_add(nor, lnor)) - 1.0);
}
