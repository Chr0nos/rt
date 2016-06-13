/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <dboudy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/13 10:45:12 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/13 11:08:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "cyl.h"

static int		rt_cyl_solve(t_cyl_inter *s, t_ray *r, t_v4d *v)
{
	(void)s;
	(void)r;
	(void)v;
	return (0);
}

int				rt_cyl_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	(void)obj;
	(void)r;
	return (rt_cyl_solve(NULL, NULL, v));
}

t_v4d			rt_cyl_normal(t_obj *obj, t_v4d *v)
{
	const t_v4d		*c = &obj->trans.w;

	return (draw_v4d_norm((t_v4d){v->x - c->x, v->y - c->y, v->z - c->z, 1.0}));
}
