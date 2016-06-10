/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/10 19:32:17 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/10 19:48:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		rt_cube_inter(t_obj *obj, t_ray *r, t_v4d *v)
{
	(void)obj;
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
	return (1);
}
