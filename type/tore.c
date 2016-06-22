/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tore.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dboudy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 16:54:26 by dboudy            #+#    #+#             */
/*   Updated: 2016/06/22 17:16:05 by dboudy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "sphere.h"

static int		rt_tore_solve(t_sphere_inter *s, t_ray *r, t_v4d *v)
{
	(void)s;
	(void)r;
	(void)v;
	return (1);
}

int				rt_tore_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	t_sphere_inter		s;

	(void)s;
	(void)obj;
	(void)r;
	(void)v;
	return (rt_tore_solve(&s, r, v));
}

t_v4d			rt_tore_normale(t_obj *obj, t_v4d *v)
{
	(void)obj;
	(void)v;
	return (*v);
}
