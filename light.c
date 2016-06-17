/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 17:29:43 by qloubier          #+#    #+#             */
/*   Updated: 2016/06/17 21:12:57 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "render.h"

static double	rt_veclen(t_v4d v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double			rt_light_pow(t_obj *obj, t_obj *light, t_v4d lnor, t_v4d vint)
{
	const t_v4d		nor = obj->normal(obj, &vint);

	(void)light;
	return (rt_veclen(draw_v4d_add(nor, lnor)) - 1.0);
}
