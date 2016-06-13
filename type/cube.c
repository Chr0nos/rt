/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 19:32:17 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/13 15:31:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	rt_cube_setpos(t_ray *r, t_v4d *v)
{
	if (v)
	{
		*v = draw_v4d_add(r->start,
			draw_v4d_mult(r->dir, (t_v4d){
				r->lenght,
				r->lenght,
				r->lenght,
				0.0
			}));
	}
}

int			rt_cube_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	(void)obj;
	rt_cube_setpos(r, v);
	return (1);
}
